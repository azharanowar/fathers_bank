#ifndef STATEMENT_H
#define STATEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "common.h"

// Function to add a new transaction record
void addNewTransactionRecord(double amount, const char *username, const char *role, const char *transactionType);

// Function to check if the statement file exists and create it if necessary
int checkStatementFile();

void displayStatement();

#endif // STATEMENT_H
