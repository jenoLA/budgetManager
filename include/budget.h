#ifndef BUDGET_H
#define BUDGET_H
#include "struct.h"

List* initList(int argc, char** argv);

Budget* searchBudget(Budget* current, char* name);

void addBudget(List* list, Budget* budget);

void deleteBudget(List* list, char* name);

Budget* initBudget(char* name);

void printBudgets(Budget* current);


#endif
