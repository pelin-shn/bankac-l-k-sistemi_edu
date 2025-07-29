#ifndef BANKA_H
#define BANKA_H

typedef enum
{
    Male,
    Female,
    Other
} Gender;

typedef struct
{
    int ID;
    char Name[50];
    char Surname[50];
    int Birthday;
    double Balance;
    Gender gender;
} User;

void start(void);

// Kullanıcı işlemleri

void deleteAccount(void);
void addUser(void);
void listUser(void);
void withdrawMoney(void);
void depositMoney(void);
void transferMoney(void);
void createAccount(User p);
#endif
