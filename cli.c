#include <stdio.h>
#include "cli.h"
#include "loglama.h"

User addUserMenu()
{
    User p;
    char genderChar;

    printf("\n--- Kullanici Ekleme ---\n");

    printf("ID: ");
    scanf("%d", &p.ID);
    // ID unique olusturulacak

    printf("Ad: ");
    scanf("%s", p.Name);
    // isim formatına uygun mu kontrol edilecek
    // örn: isim içerisinde numara olmaması lazım

    printf("Soyad: ");
    scanf("%s", p.Surname);

    printf("Doğum Tarihi (YYYYMMDD): ");
    scanf("%d", &p.Birthday);
    // aldığın değerler kontrol ediecek, bilgiler control içerisinde kontrol edilecek

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

    printf("Starting Balance: ");
    scanf("%lf", &p.Balance);
    // Balance kontrol edilecek, örn: negatif olmaması lazım, harf olmaması lazım

    if (saveUserToFile(&p)) // kaydetme işlemi banka'da olacak
    {
        printf("Kullanici başariyla eklendi.\n");
    }
    else
    {
        printf("Kullanici eklenirken hata oluştu.\n");
    }
    return p;
}

int choice()
{
    int secim;

    while (1)
    {
        printf("\n--- BANKA SİSTEMİ ---\n");
        printf("1. Kullanici Ekle\n");
        printf("2. Kullanici Sil\n");
        printf("2. Cikis\n");
        printf("Seciminizi yapiniz: ");
        scanf("%d", &secim);

        // secim integer bir deger mi kontrol edilecek

        return secim;
    }
}
void deleteUserMenu(void)
{
    int id;
    printf("\n--- Kullanici Silme ---\n");
    printf("Silmek istediginiz kullanici ID'sini girin: ");
    scanf("%d", &id);

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
