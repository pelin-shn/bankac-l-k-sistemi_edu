#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "banka.h"
#include <stdbool.h>
#include "cli.h"
#include "loglama.h"
#include "control.h"
#include "userdb.h"

#define ACCOUNT_FILE "account.txt"

char *generate_unique_id()
{
    static char id[12];
    int exists;
    FILE *fp;
    char line[256];
    char existingID[12];

    srand(time(NULL));

    do
    {
        id[0] = '1' + rand() % 9;
        for (int i = 1; i < 11; i++)
        {
            id[i] = '0' + rand() % 10;
        }
        id[11] = '\0';

        exists = 0;
        fp = fopen("account.txt", "r");
        if (!fp)
            break;

        while (fgets(line, sizeof(line), fp))
        {
            sscanf(line, "%11[^,]", existingID);
            if (strcmp(existingID, id) == 0)
            {
                exists = 1;
                break;
            }
        }
        fclose(fp);
    } while (exists);

    return id;
}

User addUserMenu()
{
    User p;

    char genderChar;

    printf("\n--- Kullanici Ekleme ---\n");

    // ID üret
    strcpy(p.ID, generate_unique_id());
    printf("Oluşturulan kullanici ID: %s\n", p.ID);

    getUserName(&p);
    getUserSurname(&p);
    p.Birthday = getUserBirthday();
    getUserGender(&p);
    p.Balance = getUserBalance();

    printf("%s,%s,%s,%d,%c,%.2lf\n",
           p.ID, p.Name, p.Surname, p.Birthday, genderChar, p.Balance);

    return p;
}

int choice()
{
    int secim;

    while (1)
    {
        printf("---BANKA YONETIM SISTEMI---\n");
        printf("1. Kullanici Ekle\n");
        printf("2. Kullanici Sil\n");
        printf("3. Kullanici Listele\n");
        printf("4. Kullanici Guncelle\n");
        printf("5. Para Cek\n");
        printf("6. Para Yatir\n");
        printf("7. Para Transferi\n");
        printf("0. Cikis\n");
        printf("Seciminizi girin: ");
        scanf("%d", &secim);

        if (secim >= 1 && secim <= 7)
            return secim;
        else
            printf("Geçerli bir seçim yapiniz (1-3).\n");
    }
}

void deleteUserMenu(void)
{
    char id[12];
    printf("\n--- Kullanici Silme ---\n");
    printf("Silmek istediginiz kullanici ID'sini girin: ");
    scanf("%11s", id);

    if (delete_user_by_id(id))
    {
        printf("Kullanici basariyla silindi.\n");
        loglama("Kullanici silindi.");
    }
    else
    {
        printf("Kullanici bulunamadi veya silinemedi.\n");
        loglama("Kullanici silinemedi.");
    }
}

void listUserMenu(void)
{
    FILE *fp = fopen(ACCOUNT_FILE, "r");
    if (fp == NULL)
    {
        printf("HATA: %s dosyasi acilamadi!\n", ACCOUNT_FILE);
        return;
    }

    char satir[256];
    printf("\n--- Kullanici Listesi ---\n");
    printf("ID\tAd\tSoyad\tDoğum Tarihi\tCinsiyet\tBakiye\n");
    printf("------------------------------------------------------------\n");

    while (fgets(satir, sizeof(satir), fp))
    {
        char *id = strtok(satir, ",");
        char *ad = strtok(NULL, ",");
        char *soyad = strtok(NULL, ",");
        char *dogumTarihi = strtok(NULL, ",");
        char *cinsiyetStr = strtok(NULL, ",");
        char *bakiyeStr = strtok(NULL, "\n");

        if (!(id && ad && soyad && dogumTarihi && cinsiyetStr && bakiyeStr))
            continue;

        // Tarihi gün/ay/yıl olarak ayırmak için
        char gun[3] = {dogumTarihi[0], dogumTarihi[1], '\0'};
        char ay[3] = {dogumTarihi[2], dogumTarihi[3], '\0'};
        char yil[5] = {dogumTarihi[4], dogumTarihi[5], dogumTarihi[6], dogumTarihi[7], '\0'};

        printf("%s\t%s\t%s\t%s/%s/%s\t%c\t%s\n",
               id, ad, soyad, gun, ay, yil, cinsiyetStr[0], bakiyeStr);
    }

    fclose(fp);
    loglama("Kullanici listelendi.");
}

void withdrawMenu(void)
{
    char id[20];
    double miktar;

    printf("\n--- Para Çekme ---\n");
    printf("ID girin: ");
    scanf("%s", id);

    printf("Çekmek istediğiniz tutar: ");
    scanf("%lf", &miktar);

    int sonuc = withdrawMoney(id, miktar);

    if (sonuc == 1)
        loglama("Para çekme işlemi başarılı.");
    else if (sonuc == -1)
        loglama("Yetersiz bakiye nedeniyle para çekilemedi.");
    else
        loglama("Geçersiz kullanıcı ID nedeniyle para çekilemedi.");
}

void depositMenu(void)
{
    char id[20];
    double miktar;

    printf("\n--- Para Yatırma ---\n");
    printf("ID girin: ");
    scanf("%s", id);

    printf("Yatırmak istediğiniz tutar: ");
    scanf("%lf", &miktar);

    bool sonuc = userDepositMoney(id, miktar);

    if (sonuc == 1)
        loglama("Para yatırma işlemi başarılı.");
    else if (sonuc == -1)
        loglama("Yetersiz bakiye nedeniyle para yatırma işlemi yapılamaz.");
    else
        loglama("Geçersiz kullanıcı ID nedeniyle para yatırma işlemi yapılamaz.");
}

void transferMenu(void)
{
    char gondericiID[20], aliciID[20];
    double miktar;

    printf("\n--- PARA TRANSFERİ ---\n");
    printf("Gönderen kullanıcı ID: ");
    scanf("%s", gondericiID);

    printf("Alıcı kullanıcı ID: ");
    scanf("%s", aliciID);

    printf("Gönderilecek tutar (TL): ");
    scanf("%lf", &miktar);

    if (!userTransferMoney(gondericiID, aliciID, miktar))
    {
        printf("Transfer işlemi başarısız.\n");
    }
}

// Henüz uygulanmayan fonksiyonlar
void updateUserMenu(void)
{
    printf("Kullanici güncelleme menüsü (henüz uygulanmadi).\n");
}

void getUserName(User *p)
{
    while (1)
    {
        printf("Kullanici adini girin: ");
        scanf("%49s", p->Name);

        if (!checkUserName(p->Name))
        {
            return;
        }
        printf("Kullanici adi geçersiz! Lütfen harflerden oluşan bir isim girin.\n");
        loglama("Kullanici ekleme basarisiz: Geçersiz kullanıcı adı.");
    }
}

void getUserSurname(User *p)
{
    while (1)
    {
        printf("Kullanici soyadini girin: ");
        scanf("%49s", p->Surname);

        if (!checkUserSurname(p->Surname))
        {
            return;
        }
        printf("Kullanici soyadi geçersiz! Lütfen geçerli bir soyisim girin.\n");
        loglama("Kullanici ekleme basarisiz: Geçersiz kullanici soyadi.");
    }
}

int getUserBirthday()
{
    int day, month, year;
    while (1)
    {
        printf("Doğum Tarihi (DD MM YYYY): ");
        scanf("%d %d %d", &day, &month, &year);

        if (!checkUserBirthday(day, month, year))
        {
            printf("Doğum tarihi: %02d/%02d/%04d\n", day, month, year);
            // DDMMYYYY formatında döndür
            return day * 1000000 + month * 10000 + year;
        }
        printf("Doğum tarihi geçersiz! Lütfen 1-31 gün, 1-12 ay ve 1900-2100 yil araliginda bir tarih girin.\n");
        loglama("Kullanici ekleme basarisiz: Geçersiz doğum tarihi.");
    }
}

void printUserInfo(const User p)
{
    printf("Kullanici Bilgileri:\n");
    printf("ID: ");
    printCharList(p.ID, 12);
    printf("Ad: ");
    printCharList(p.Name, 50);
    printf("Soyad: ");
    printCharList(p.Surname, 50);
    printf("Dogum Tarihi: %d\n", p.Birthday);
    printf("Cinsiyet: %c\n", (convertGenderToStr(p.gender)));
    printf("Bakiye: %.2lf\n", p.Balance);
}

char convertGenderToStr(Gender g)
{
    char genderStr;
    switch (g)
    {
    case Male:
        genderStr = 'M';
        break;
    case Female:
        genderStr = 'F';
        break;
    default:
        genderStr = 'O';
        break;
    }
    return genderStr;
}

void printCharList(const char *list, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        if (list[i] == '\0')
            break;
        printf("%c", list[i]);
    }
    printf("\n");
}

void getUserGender(User *p)
{
    char genderChar;
    printf("Cinsiyet (M/F/O): ");
    scanf(" %c", &genderChar);
    switch (genderChar)
    {
    case 'M':
    case 'm':
        p->gender = Male;
        break;
    case 'F':
    case 'f':
        p->gender = Female;
        break;
    default:
        p->gender = Other;
        break;
    }
}

double getUserBalance(void)
{
    char input[100];
    double balance;

    while (1)
    {
        printf("Başlangiç Bakiyesi: ");
        scanf("%99s", input);

        if (!checkUserBalance(input)) // sadece rakamsa true
        {
            balance = strtod(input, NULL);
            return balance;
        }
        else
        {
            printf("Geçersiz bakiye! Lütfen sadece rakamlardan oluşan bir değer girin.\n");
            loglama("Kullanici ekleme başarisiz: Geçersiz bakiye.");
        }
    }
}