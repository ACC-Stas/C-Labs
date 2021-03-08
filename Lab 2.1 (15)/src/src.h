#pragma once

int getIntCommand(int lowBound, int highBound);
void setDate(int* day, int* month, int* year);
int calculateLength(int beginDay, int beginMonth, int beginYear, int endDay, int endMonth, int endYear); /*return number of days or -1 if impossible*/
long long getProgrammersCost(int workLength, int  rate, int employeesNumber); /*return - 1, if not enough data*/