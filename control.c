#include "control.h"
#include <stdio.h>
#include "banka.h"
#include "userdb.h"

int isValidDay(int day)
{
    return (day >= 1 && day <= 31);
}

bool checkUserName(const char *name)
{
    if (name == NULL || name[0] == '\0')
    {

        return true;
    }
    else if (checkUserNameChars(name))
    {
        return true;
    }

    return false;
}

bool checkUserNameChars(const char *name)

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