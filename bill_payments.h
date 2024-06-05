#include <stdio.h>
#include "common.h"

#define TRANSACTION_FILE "statement.txt"

extern double currentBalance;
extern char currentUsername[20];
extern char currentUserRole[20];

void readBalanceFromFile(); // Declare functions from account.c
void saveBalanceToFile();
double getCurrentBalance();

void billPayments();
void payElectricityBill();
void payGasBill();
void payTransportationBill();