#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cli.h"
#include "loglama.h"
#include "control.h"

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
    int day, mounth, year;

    printf("\n--- Kullanici Ekleme ---\n");

    // ID üret
    strcpy(p.ID, generate_unique_id());
    printf("Oluşturulan kullanici ID: %s\n", p.ID);

    getUserName();

    printf("Soyad: ");
    scanf("%s", p.Surname);

    printf("Doğum Tarihi (day mounth year): ");
    scanf("%d %d %d", &day, &mounth, &year);

    // Tarih kontrolü (gün 1-31 arası mı?)
    if (!isValidDay(day))
    {
        printf("Hatali gün girdiniz! 1-31 arasinda olmali.\n");
        loglama("Kullanici ekleme başarisiz: Geçersiz gün.");
        strcpy(p.ID, "");
        return p;
    }
    p.Birthday = day * 1000000 + mounth * 10000 + year;

    printf("Cinsiyet (M/F/O): ");
    scanf(" %c", &genderChar);

    switch (genderChar)
    {
    case 'M':
    case 'm':
        p.gender = Male;
        break;
    case 'F':
    case 'f':
        p.gender = Female;
        break;
    default:
        p.gender = Other;
        break;
    }

    printf("Başlangic Bakiyesi: ");
    scanf("%lf", &p.Balance);

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

// Henüz uygulanmayan fonksiyonlar
void updateUserMenu(void)
{
    printf("Kullanici güncelleme menüsü (henüz uygulanmadi).\n");
}

void listUserMsg(void)
{
    printf("Kullanici listeleme menüsü (henüz uygulanmadi).\n");
}

void depositMenu(void)
{
    printf("Para yatirma menüsü (henüz uygulanmadi).\n");
}

void withdrawMenu(void)
{
    printf("Para çekme menüsü (henüz uygulanmadi).\n");
}

void transferMenu(void)
{
    printf("Para transfer menüsü (henüz uygulanmadi).\n");
}

void getUserName()
{
    while (1)
    {
        char name[50];
        printf("Kullanici adini girin: ");
        scanf("%49s", name);

        if (!checkUserName(name))
        {
            return;
        }
        printf("Kullanici adi geçersiz! Lütfen harflerden oluşan bir isim girin.\n");
        loglama("Kullanici ekleme basarisiz: Geçersiz kullanıcı adı.");
    }
}