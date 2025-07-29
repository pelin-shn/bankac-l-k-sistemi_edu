#include <stdio.h>
#include <string.h>
#include "userdb.h"

#define ACCOUNT_FILE "account.txt"
#define TEMP_FILE "temp.txt"

int saveUserToFile(const User *p)
{
    FILE *fp = fopen(ACCOUNT_FILE, "a");
    if (fp == NULL)
    {
        return 1; // Başarısız
    }

    char genderChar;
    switch (p->gender)
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

    fprintf(fp, "%d,%s,%s,%d,%c,%.2lf\n",
            p->ID, p->Name, p->Surname, p->Birthday, genderChar, p->Balance);

    fclose(fp);
    return 0; // Başarılı
}

int update_user_in_file(const User *updatedUser)
{ // Belirli ID'ye sahip kullanıcıyı güncelle
    FILE *fp = fopen(ACCOUNT_FILE, "r");
    FILE *temp = fopen(TEMP_FILE, "w");

    if (!fp || !temp)
        return 1;

    int updated = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp))
    {
        int readID;
        sscanf(line, "%d,", &readID);

        if (readID == updatedUser->ID)
        {
            char genderChar = (updatedUser->gender == Male) ? 'M' : (updatedUser->gender == Female) ? 'F'
                                                                                                    : 'O';

            fprintf(temp, "%d,%s,%s,%d,%c,%.2f\n",
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

int checkUserExists(int id)
{ // Belirli ID'ye sahip kullanıcının varlığını kontrol et
    FILE *fp = fopen(ACCOUNT_FILE, "r");
    if (!fp)
        return 0;

    char line[256];
    int readID;

    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d,", &readID);
        if (readID == id)
        {
            fclose(fp);
            return 1; // ID zaten var
        }
    }

    fclose(fp);
    return 0; // ID yok, kullanılabilir
}

int delete_user_by_id(int id)
{
    FILE *fp = fopen(ACCOUNT_FILE, "r");
    FILE *temp = fopen(TEMP_FILE, "w");

    if (!fp || !temp)
        return 0;

    char line[256];
    int readID;
    int deleted = 0;

    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d,", &readID);
        if (readID == id)
        {
            deleted = 1;
            continue; // Kullanıcıyı atla (sil)
        }
        fputs(line, temp); // Diğer kullanıcıları geçici dosyaya yaz
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
        perror("Gecici dosya yeniden adlandirilamadi");
        return 0;
    }

    return deleted;
}
