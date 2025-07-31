#ifndef CLI_H
#define CLI_H

#include "userdb.h"

// Menü fonksiyonları
// void main_menu();
int choice();
User addUserMenu(void);

// Kullanıcı işlemleri arayüzleri (CLI)
void createUserMenu(void);
void deleteUserMenu(void);
void updateUserMenu(void);
void listUserMenu(void);

void depositMenu(void);
void withdrawMenu(void);
void transferMenu(void);

void getUserName(User *p);
void getUserSurname(User *p);
int getUserBirthday(void);
void getUserGender(User *p);
double getUserBalance(void);

char convertGenderToStr(const Gender g);
void printUserInfo(const User p);
void printCharList(const char *list, size_t size);

#endif
