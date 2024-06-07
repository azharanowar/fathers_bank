#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "common.h"

extern double currentBalance;

void readBalanceFromFile();
void saveBalanceToFile();
double getCurrentBalance();

#endif // ACCOUNT_H
