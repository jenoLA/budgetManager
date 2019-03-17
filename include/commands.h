#ifndef COMMANDS_H
#define COMMANDS_H
#include "struct.h"

//help welcomeMessage
void welcomeMessage();

// print files in the given folder
void printFilesInFolder(char* path);

// main menu, it is here to make CLI easier
void mainMenu(char* path, char const* file);

// paper message
void paperMenuMessage(Budget* budget);

// paper menu
int paperMenu(Budget* budget);

#endif