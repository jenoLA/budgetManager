#ifndef PAPER_H
#define PAPER_H
#include "paper.h"

// user will be asked for the required data 
Paper* createPaper();

// requesting char code[6] for better integration with the system
Paper* searchPaper(Paper* current, char code[6]);

// puts on the last position
void addPaper(Budget* budget, Paper* paper);

void deletePaper(Budget* budget, char code[6]);

// print all the info about the papers
void listPapers(Paper* current);

// data required within
void updatePaper();


#endif
