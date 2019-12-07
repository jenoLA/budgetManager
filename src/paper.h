#pragma once
#include "struct.h"

// create a list of papers
List* initList(char* path, char const* file); 

// user will be asked for the required data outside the function
Paper* createPaper(char* code, float value, int quantity);

// requesting the code for better integration with the system
Paper* searchPaper(Paper* paper, char* code);

// puts on the last position
int addPaper(List* list, Paper* paper);

//delete a paper
int deletePaper(List* list, char *code);

// print all the info about the papers
void listPapers(Paper* current);

int trade(List* list, Paper* paper, float value, int quantity);

void simulateTrade(Paper* paper, float value, int quantity);
// simulate a trade
void simulateSell(Paper* paper, float value, int quantityMinus);

// simulate a buy trade
void simulateBuy(Paper* paper, float value, int quantityPlus);

// maybe in the future make a more detailed view of a single paper
