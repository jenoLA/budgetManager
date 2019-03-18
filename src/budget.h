#ifndef BUDGET_H
#define BUDGET_H
#include "struct.h"

//if is a valid path/file return the readed one from there, else a new
List* initList(char* path, char const* file); 

//search a budget by its name
Budget* searchBudget(Budget* current, char const* name);

//append the budget on the end of the current list
int addBudget(List* list, Budget* budget);

//delete the budget from the current list
int deleteBudget(List* list, char const* name);

//initialize the budget
Budget* initBudget(char const* name);

//print informations about all the budgets
void printBudgets(Budget* current);


#endif
