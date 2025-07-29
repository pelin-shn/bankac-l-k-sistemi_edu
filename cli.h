#ifndef CLI_H
#define CLI_H

#include "userdb.h"

// Menü fonksiyonları
// void main_menu();
int choice();
User addUserMenu(void);

// Kullanıcı işlemleri arayüzleri (CLI)
void create_user_menu(void);
void delete_user_menu(void);
void update_user_menu(void);
void list_user_msg(void);

// Banka işlemleri arayüzleri
void create_account_menu(void);
void delete_account_menu(void);
void deposit_menu(void);
void withdraw_menu(void);
void transfer_menu(void);

#endif
