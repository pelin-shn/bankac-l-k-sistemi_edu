#include "banka.h"
#include "loglama.h"
#include "userdb.h"
#include <stdio.h>
#include "cli.h"

void createAccount(User p)
{

    if (check_user_exists(p.ID))
    {
        printf("Bu ID zaten mevcut! Lütfen farkli bir ID girin.\n");
        loglama("Kullanici eklenemedi: ID zaten mevcut.");
        return;
    }

    if (saveUserToFile(&p))
    {
        printf("Kullanici başariyla eklendi.\n");
        loglama("Yeni kullanici eklendi.");
    }
    else
    {
        printf("Kullanici eklenirken hata oluştu.\n");
        loglama("Kullanici eklenemedi!");
    }
}

void start(void)
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

        // Kullanıcı işlemleri.
        switch (secim)
        {
        case 1:
        {
            User newUser = addUserMenu(); // Kullanıcıdan verileri al
            createAccount(newUser);       // Dosyaya kaydet
            break;
        }
        case 2:
            deleteUserMenu();
            break;
        case 3:
            updateUserMenu();
            break;
        case 4:
            listUserMenu();
            break;
        case 5:
            depositMenu();
            break;
        case 6:
            withdrawMenu();
            break;
        case 7:
            transferMenu();
            break;
        case 0:
            printf("Programdan cikiliyor...\n");
            return;
        default:
            printf("Geçersiz secim! Lütfen tekrar deneyin.\n");
        }
    }
}
