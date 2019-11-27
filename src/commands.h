#pragma once
#include "struct.h"

//help welcomeMessage
void welcomeMessage();

// print files in the given folder
void printFilesInFolder(char* path);

// main menu, it is here to make CLI easier
void mainMenu(char* path, char const* file);
