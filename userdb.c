#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userdb.h"

#define ACCOUNT_FILE "account.txt"
#define TEMP_FILE "temp.txt"

int saveUserToFile(const User p)
{
    FILE *fp = fopen(ACCOUNT_FILE, "a");
    if (fp == NULL)
    {
        return 1; // Başarısız
    }

    char genderChar;
    switch (p.gender)
    {
    case Male:
        genderChar = 'M';
        break;
    case Female:
        genderChar = 'F';
        break;
    default:
        genderChar = 'O';
        break;
    }

    fprintf(fp, "%s,%s,%s,%d,%c,%.2lf\n",
            p.ID, p.Name, p.Surname, p.Birthday, genderChar, p.Balance);
    fclose(fp);
    return 0; // Başarılı
}

int update_user_in_file(const User *updatedUser)
{
    FILE *fp = fopen(ACCOUNT_FILE, "r");
    FILE *temp = fopen(TEMP_FILE, "w");

    if (!fp || !temp)
        return 1;

    int updated = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp))
    {
        char readID[12];
        sscanf(line, "%11[^,]", readID);

        if (strcmp(readID, updatedUser->ID) == 0)
        {
            char genderChar = (updatedUser->gender == Male) ? 'M' : (updatedUser->gender == Female) ? 'F'
                                                                                                    : 'O';

            fprintf(temp, "%s,%s,%s,%d,%c,%.2f\n",
                    updatedUser->ID,
                    updatedUser->Name,
                    updatedUser->Surname,
                    updatedUser->Birthday,
                    genderChar,
                    updatedUser->Balance);
            updated = 1;
        }
        else
        {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(ACCOUNT_FILE);
    rename(TEMP_FILE, ACCOUNT_FILE);

    return updated;
}

int checkUserExistsInDB(char *ID)
{
    FILE *fp = fopen(ACCOUNT_FILE, "r");
    if (!fp)
        return 0;

    char line[256];
    char existingID[12];

    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%11[^,]", existingID);
        if (strcmp(existingID, ID) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0; // ID yok, kullanılabilir
}

int delete_user_by_id(const char *ID)
{
    FILE *fp = fopen(ACCOUNT_FILE, "r");
    FILE *temp = fopen(TEMP_FILE, "w");

    if (!fp || !temp)
        return 0;

    char line[256];
    char readID[12];
    int deleted = 0;

    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%11[^,]", readID);

        if (strcmp(readID, ID) == 0)
        {
            deleted = 1;
            continue; // Bu satırı atla
        }

        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    if (remove(ACCOUNT_FILE) != 0)
    {
        perror("Orijinal dosya silinemedi");
        return 0;
    }

    if (rename(TEMP_FILE, ACCOUNT_FILE) != 0)
    {
        perror("Geçici dosya yeniden adlandirilamadi");
        return 0;
    }

    return deleted;
}

void listeleKullanicilar(void)
{
    FILE *fp = fopen(ACCOUNT_FILE, "r");
    if (fp == NULL)
    {
        printf("HATA: %s dosyası açılamadı!\n", ACCOUNT_FILE);
        return;
    }

    char satir[256];

    printf("---------------------------------------------------------------------------------\n");
    printf("ID         | Ad       | Soyad    | Dogum Tarihi | Cinsiyet | Bakiye\n");
    printf("---------------------------------------------------------------------------------\n");

    while (fgets(satir, sizeof(satir), fp))
    {
        // Satırı virgül ile ayır
        char *id = strtok(satir, ",");
        char *ad = strtok(NULL, ",");
        char *soyad = strtok(NULL, ",");
        char *gunStr = strtok(NULL, ",");
        char *ayStr = strtok(NULL, ",");
        char *yilStr = strtok(NULL, ",");
        char *cinsiyetStr = strtok(NULL, ",");
        char *bakiyeStr = strtok(NULL, "\n");

        if (id && ad && soyad && gunStr && ayStr && yilStr && cinsiyetStr && bakiyeStr)
        {
            int gun = atoi(gunStr);
            int ay = atoi(ayStr);
            int yil = atoi(yilStr);
            double bakiye = atof(bakiyeStr);

            printf("%-11s | %-8s | %-8s | %02d/%02d/%04d | %-8s | %.2lf\n",
                   id, ad, soyad, gun, ay, yil, cinsiyetStr, bakiye);
        }

        printf("---------------------------------------------------------------------------------\n");

        fclose(fp);
    }
}