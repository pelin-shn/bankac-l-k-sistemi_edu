#include <stdio.h>
#include "control.h"
#include "banka.h"
#include "userdb.h"

void User_update()
{ // Kullanici ekleme
    User p;
    char genderChar;

    printf("ID: ");
    scanf("%d", &p.ID);

    if (checkUserExists(p.ID))
    {
        printf("Bu ID zaten mevcut! Lütfen farkli bir ID girin.\n");
        loglama("Kullanici eklenemedi: ID zaten mevcut.");
        return;
    }

    printf("Name: ");
    scanf("%s", p.Name);

    printf("Surname: ");
    scanf("%s", p.Surname);

    printf("Birthdate (YYYYMMDD): ");
    scanf("%d", &p.Birthday);

    printf("Gender (M/F/O): ");
    scanf(" %c", &genderChar);
    if (genderChar == 'M' || genderChar == 'm')
        p.gender = Male;
    else if (genderChar == 'F' || genderChar == 'f')
        p.gender = Female;
    else
        p.gender = Other;

    printf("Current Balance: ");
    scanf("%lf", &p.Balance);

    if (saveUserToFile(&p))
    {
        printf("User saved successfully.\n");
        loglama("Yeni kullanici eklendi.");
    }
    else
    {
        printf("Failed to save user.\n");
        loglama("Kullanici eklenemedi!");
    }
}
