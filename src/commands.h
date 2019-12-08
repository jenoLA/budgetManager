#pragma once
#include "struct.h"

void welcomeMessage();

void printFilesInFolder(char* path);

void copyContent(char *source, char *destination);

void backup(char *path, char *file);

void restore(char *path, char *file);

void deleteFile(char *path, char *file);

void clean_stdin();

void mainMenu(char* path, char const* file);
