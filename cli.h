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
void listUserMsg(void);

// Banka işlemleri arayüzleri
void createAccountMenu(void);
void deleteAccountMenu(void);
void depositMenu(void);
void withdrawMenu(void);
void transferMenu(void);

#endif
