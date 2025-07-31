#include "control.h"
#include <stdio.h>
#include <stdlib.h>
#include "banka.h"
#include "userdb.h"
#include "stdbool.h"

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
