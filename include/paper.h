#ifndef PAPER_H
#define PAPER_H
#include "struct.h"

// user will be asked for the required data 
Paper* createPaper();

// requesting char code[6] for better integration with the system
Paper* searchPaper(Paper* current, char* string);

// puts on the last position
void addPaper(Budget* budget, Paper* paper);

void deletePaper(Budget* budget);

// print all the info about the papers
void listPapers(Paper* current);

// data required within
void updatePaper(Budget* budget, Paper* paper);

// simulate a sell
void simulateSell(Paper* paper);

// welcome message
void paperMenuMessage(Budget* budget);

// menu to handle papers within the given budget
void paperMenu(Budget* budget);


#endif
