#ifndef PAPER_H
#define PAPER_H
#include "struct.h"

// user will be asked for the required data outside the function
Paper* createPaper(char* code, float value, int quantity);

// requesting char code[6] for better integration with the system
Paper* searchPaper(Paper* current, char* string);

// puts on the last position
int addPaper(Budget* budget, Paper* paper);

//delete a paper
int deletePaper(Budget* budget, char* code);

// print all the info about the papers
int listPapers(Paper* current);

//update paper selling him
int updatePaperSell(Budget* budget, Paper* paper, float value, int quantity);

//update paper buying him
int updatePaperBuy(Budget* budget, Paper* paper, float value, int quantity);

// simulate a trade
void simulateSell(Paper* paper, float value, int quantity);
// maybe in the future make a more detailed view of a single paper

#endif
