// withdraw.h
#ifndef WITHDRAW_H
#define WITHDRAW_H

int withdraw(double amount);
int canWithdraw(double amount, const char *role);
void updateWithdrawLimits(double amount);

#endif // WITHDRAW_H
