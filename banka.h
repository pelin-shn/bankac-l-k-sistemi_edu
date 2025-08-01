#ifndef BANKA_H
#define BANKA_H

#include <stdbool.h>

typedef enum
{
    Male,
    Female,
    Other
} Gender;

typedef struct
{
    char ID[12];
    char Name[50];
    char Surname[50];
    int Birthday;
    double Balance;
    Gender gender;
} User;

void start(void);

// Kullanıcı işlemleri

void deleteUser(void);
void addUser(void);
void listUser(void);
void withdrawMenu(void);
void depositMoney(void);
void transferMoney(void);
void createUser(void);
#endif
