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
bool checkIfIntNotExist(const char *name);
bool checkUserSurname(const char *surname);
bool checkUserSurnameChars(const char *surname);
bool checkUserBirthday(int day, int month, int year);
bool checkUserBalance(const char *balanceStr);
bool withdrawMoney(const char *id, double amount);
bool userDepositMoney(const char *id, double amount);
#endif
