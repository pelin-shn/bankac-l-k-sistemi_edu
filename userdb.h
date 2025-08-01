#ifndef USERDB_H
#define USERDB_H

#include "banka.h"

int saveUserToFile(const User p);
int delete_user_by_id(const char *ID);
int update_user_in_file(const User *p);
int checkUserExistsInDB(char *ID);
void listeleKullanicilar(void);
bool withdrawMoney(const char *id, double amount);
#endif
