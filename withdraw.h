// withdraw.h
#ifndef WITHDRAW_H
#define WITHDRAW_H

#include "withdraw.h"
#include "statement.c"

#define MAX_WITHDRAW_AMOUNT_DAILY 1000
#define MAX_WITHDRAW_AMOUNT_MONTHLY 5000
#define FATHER_ROLE "Father"
#define TRANSACTION_FILE "statement.txt"

void withdrawMoney();
int canWithdraw(double amount, const char *role);

extern double currentBalance;
extern char currentUsername[20];
extern char currentUserRole[20];

void readBalanceFromFile(); // Declare functions from account.c
void saveBalanceToFile();
double getCurrentBalance();

double getDailyWithdrawn();
double getMonthlyWithdrawn();

int canWithdraw(double amount, const char *currentUserRole);

#endif // WITHDRAW_H
