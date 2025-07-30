#ifndef CONTROL_H
#define CONTROL_H
#include <stdbool.h>
#include "userdb.h"
#include "loglama.h"
#include <stdio.h>

int isValidDay(int day);
void checkUserInfo(void);
int checkUserExists(const char *id);
bool checkUserName(const char *name);
bool checkUserNameChars(const char *name);

#endif
