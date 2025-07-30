#include "banka.h"
#include "loglama.h"
#include "userdb.h"
#include <stdio.h>
#include "cli.h"

void createAccount()
{

    User newUser = addUserMenu();

    if (checkUserExistsInDB(newUser.ID))
    {
        printf("Bu ID zaten mevcut! Lütfen farkli bir ID girin.\n");
        loglama("Kullanici eklenemedi: ID zaten mevcut.");
        return;
    }

    if (saveUserToFile(&newUser))
    {
        printf("Kullanici eklenirken hata oluştu.\n");
        loglama("Kullanici eklenemedi!");
    }
    else
    {
        printf("Kullanici başariyla eklendi.\n");
        loglama("Yeni kullanici eklendi.");
    }
}

void start(void)
{
    int secim;

    while (1)
    {
        secim = choice();

        // Kullanıcı işlemleri.
        switch (secim)
        {
        case 1:
        {
            createAccount(); // Dosyaya kaydet
            break;
        }
        case 2:
            deleteUserMenu();
            break;
        case 3:
            updateUserMenu();
            break;
        case 4:
            listUserMsg();
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
