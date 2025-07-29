#ifndef USERDB_H
#define USERDB_H

#include "banka.h"

int save_user_to_file(const User *p);
int delete_user_from_file(int id);
int update_user_in_file(const User *p);
int check_user_exists(int ID);

#endif