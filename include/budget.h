#ifndef BUDGET_H
#define BUDGET_H
#include "struct.h"

//if argv[1] is a valid data file return the readed one from there
List* initList(int argc, char const *argv[]); 

//search a budget by its name
Budget* searchBudget(Budget* current, char* name);

//append the budget on the end of the current list
void addBudget(List* list, Budget* budget);

//delete the budget from the current list
void deleteBudget(List* list, char* name);

//initialize the budget
Budget* initBudget(char* name);

//print informations about all the budgets
void printBudgets(Budget* current);


#endif
