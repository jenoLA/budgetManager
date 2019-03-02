#ifndef BUDGET_H
#define BUDGET_H


List* initList();

Budget* searchBudget(Budget* current, char* name);

void addBudget(List* list, Budget* budget);

void deleteBudget(List* list, char* name);

Budget* initBudget(char* name);

void printBudgets(Budget* current);

void readList();

void saveList(List* list);

#endif
