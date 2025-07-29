#ifndef USERDB_H
#define USERDB_H

#include "banka.h"

int saveUserToFile(const User *p);
int delete_user_by_id(int id);
int update_user_in_file(const User *p);
int checkUserExists(int ID);

#endif
