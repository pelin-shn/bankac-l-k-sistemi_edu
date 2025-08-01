#include "control.h"
#include <stdio.h>
#include <stdlib.h>
#include "banka.h"
#include "userdb.h"
#include "stdbool.h"
#include <string.h>

/*int isValidDay(int day)
{
    return (day >= 1 && day <= 31);
}*/

bool checkUserName(const char *name)
{
    if (name == NULL || name[0] == '\0')
    {

        return true;
    }
    else if (checkIfIntNotExist(name))
    {
        return true;
    }

    return false;
}

bool checkIfIntNotExist(const char *name)

{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')))
        {
            return true; // Geçersiz karakter bulundu
        }
    }
    return false;
}

bool checkUserSurname(const char *surname)
{
    if (surname == NULL || surname[0] == '\0')
    {
        return true;
    }
    else if (checkIfIntNotExist(surname))
    {
        return true;
    }

    return false;
}

bool checkUserSurnameChars(const char *surname)

{
    for (int i = 0; surname[i] != '\0'; i++)
    {
        if (!((surname[i] >= 'A' && surname[i] <= 'Z') || (surname[i] >= 'a' && surname[i] <= 'z')))
        {
            return true; // Geçersiz karakter bulundu
        }
    }
    return false;
}

bool checkUserBirthday(int day, int month, int year)
{
    if (day < 1 || day > 31 || month < 1 || month > 12)
    {
        return true; // Geçersiz gün veya ay
    }

    // Basit bir yıl kontrolü
    if (year < 1900 || year > 2100)
    {
        return true; // Geçersiz yıl
    }

    // Şubat ayı için özel kontrol
    if (month == 2)
    {
        if (day > 29)
        {
            return true; // Şubat'ta 29'dan fazla gün olamaz
        }
        if (day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
        {
            return true; // Artık yıl değilse Şubat'ta 29 olamaz
        }
    }

    return false;
}

bool checkUserBalance(const char *balanceStr)
{
    if (balanceStr == NULL || balanceStr[0] == '\0')
        return true;

    int dotCount = 0;

    for (int i = 0; balanceStr[i] != '\0'; i++)
    {
        if (!((balanceStr[i] >= '0' && balanceStr[i] <= '9')))
        {
            if (balanceStr[i] == '.')
            {
                dotCount++;
                if (dotCount > 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

bool withdrawMoney(const char *id, double amount)
{
    FILE *fp = fopen("account.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp)
    {
        printf("Dosya açma hatası!\n");
        return 0;
    }

    char satir[256];
    int bulundu = 0; // İlk başta kullanıcı bulunmadı
    int islemBasarili = 0;

    while (fgets(satir, sizeof(satir), fp))
    {
        char ID[20], ad[30], soyad[30], cinsiyet;
        int tarih;
        double bakiye;

        // Satırdaki verileri doğru şekilde ayıklamak için yeni sscanf formatı
        int okunan = sscanf(satir, "%[^,],%[^,],%[^,],%d,%c,%lf",
                            ID, ad, soyad, &tarih, &cinsiyet, &bakiye);

        if (okunan == 6)
        {
            // Yeni satır karakterini temizlemek için
            ID[strcspn(ID, "\n")] = 0; // ID'nin sonundaki \n'yi sil

            // Kullanıcı ID'sini kontrol et
            if (strcmp(ID, id) == 0)
            {
                bulundu = 1;
                if (bakiye >= amount)
                {
                    bakiye -= amount;
                    printf("\nPara başarıyla çekildi!\n");
                    islemBasarili = 1;
                }
                else
                {
                    printf("\nYetersiz bakiye!\n");
                    islemBasarili = -1;
                }
            }

            // Güncellenmiş bakiyeyi kaydet
            fprintf(temp, "%s,%s,%s,%d,%c,%.2lf\n",
                    ID, ad, soyad, tarih, cinsiyet, bakiye);
        }
        else
        {
            // Verisi düzgün olmayan satırı olduğu gibi geç
            fputs(satir, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("account.txt");
    rename("temp.txt", "account.txt");

    if (!bulundu)
    {
        printf("\nKullanıcı bulunamadı!\n");
        return 0;
    }

    if (islemBasarili == 1)
    {
        printf("\nBakiye başarıyla güncellendi. Ana menüye dönülüyor...\n");
    }

    return islemBasarili;
}

bool userDepositMoney(const char *id, double amount)
{
    FILE *fp = fopen("account.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp)
    {
        printf("Dosya açma hatası!\n");
        return 0;
    }

    char satir[256];
    int bulundu = 0;
    int islemBasarili = 0;

    while (fgets(satir, sizeof(satir), fp))
    {
        char ID[20], ad[30], soyad[30], cinsiyet;
        int tarih;
        double bakiye;

        int okunan = sscanf(satir, "%[^,],%[^,],%[^,],%d,%c,%lf",
                            ID, ad, soyad, &tarih, &cinsiyet, &bakiye);

        if (okunan == 6)
        {
            // Yeni satır karakterini temizlemek için
            ID[strcspn(ID, "\n")] = 0;

            // Kullanıcı ID'sini kontrol et
            if (strcmp(ID, id) == 0)
            {
                bulundu = 1;
                bakiye += amount; // Para yatırma işlemi, bakiyeyi artır
                printf("\nPara başarıyla yatırıldı!\n");
                islemBasarili = 1;
            }

            // Güncellenmiş bakiyeyi kaydet
            fprintf(temp, "%s,%s,%s,%d,%c,%.2lf\n",
                    ID, ad, soyad, tarih, cinsiyet, bakiye);
        }
        else
        {
            // Verisi düzgün olmayan satırı olduğu gibi geç
            fputs(satir, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("account.txt");
    rename("temp.txt", "account.txt");

    if (!bulundu)
    {
        printf("\nKullanıcı bulunamadı!\n");
        return 0;
    }

    if (islemBasarili == 1)
    {
        printf("\nBakiye başarıyla güncellendi. Ana menüye dönülüyor...\n");
    }

    return islemBasarili;
}

bool userTransferMoney(const char *senderID, const char *receiverID, double amount)
{
    if (strcmp(senderID, receiverID) == 0)
    {
        printf("Gönderen ve alıcı aynı kullanıcı olamaz.\n");
        return false;
        loglama("Para transferi başarısız: Gönderen ve alıcı aynı kullanıcı.");
    }

    if (amount <= 0)
    {
        printf("Geçersiz tutar! Tutar 0'dan büyük olmalıdır.\n");
        return false;
        loglama("Para transferi başarısız: Geçersiz tutar.");
    }

    if (!withdrawMoney(senderID, amount))
    {
        printf("Para çekme işlemi başarısız.\n");
        return false;
        loglama("Para transferi başarısız: Gönderen kullanıcıdan para çekilemedi.");
    }

    if (!userDepositMoney(receiverID, amount))
    {
        printf("Para yatırma işlemi başarısız. Gönderilen tutar geri iade ediliyor.\n");
        userDepositMoney(senderID, amount); // Geri iade
        return false;
        loglama("Para transferi başarısız: Alıcı kullanıcıya para yatırma işlemi başarısız.");
    }

    printf("Para transferi başarılı!\n");
    return true;
    loglama("Para transferi başarılı.");
}