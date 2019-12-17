#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include "paper.h"
#include "commands.h"

void welcomeMessage()
{
	printf("\033[36m");
	printf(" Budget Manager");
	printf("\033[m");
	printf("\n\n");
}

void helpMessage()
{
	const char* turnTextYellow = "\033[33m";
	const char* turnTextBlue = "\033[36m";
	const char* turnTextWhite = "\033[m";
	printf("A command line utility to manage financial actives.\n");
	printf("You can use it by its menu or via command line parameters.\n");
	printf("[usage]: bgtmanager %s[PARAMETERS] %s...%s\n", turnTextBlue, turnTextYellow, turnTextWhite);
	printf("         bgtmanager %s<data file> %s...%s\n", turnTextYellow, turnTextBlue, turnTextWhite);
	printf(" with no arguments goes to menu\n\n");
	printf("%s[PARAMETERS]%s:\n\n", turnTextBlue, turnTextWhite);

	printf("%s -l, --list%s\n", turnTextBlue, turnTextWhite);
	printf("	print out all saved files\n\n");

	printf("%s -r, --restore %s<data file>%s\n", turnTextBlue, turnTextYellow, turnTextWhite);
	printf("	restore the given data file to a early state\n\n");

	printf("%s -d, --delete %s<data file>%s\n", turnTextBlue, turnTextYellow, turnTextWhite);
	printf("	delete the given data file\n\n");

	printf("%s -b, --backup %s<data file>%s\n", turnTextBlue, turnTextYellow, turnTextWhite);
	printf("	backup the given data file\n\n");

	printf("%s <data file> %s...%s :\n", turnTextYellow, turnTextBlue, turnTextWhite);
	printf("	load given data file and if no more argument is provided goes to the menu\n\n");

	printf("%s <data file> %s-l, --list%s\n", turnTextYellow, turnTextBlue, turnTextWhite);
	printf("	print out all the actives in the file\n\n");

	printf("%s <data file> %s-d, --delete <code>%s\n", turnTextYellow, turnTextBlue, turnTextWhite);
	printf("	delete an existing paper\n\n");

	printf("%s <data file> %s-t, --trade <code> <value> <quantity>%s\n", turnTextYellow, turnTextBlue, turnTextWhite);
	printf("	trade an existing paper, negative quantity means sell, positive quantity means buy\n\n");

	printf("%s <data file> %s-T, --simulate-trade <code> <value> <quantity>%s\n", turnTextYellow, turnTextBlue, turnTextWhite);
	printf("	simulate a trade of an existing paper\n\n");
}

void copyContent(char* destination, char* source)
{
	FILE* src = fopen(source, "rb");
	if(!src)
	{
		printf("Invalid file\n");
		return;
	}

	FILE* dest = fopen(destination, "wb");
	if(!dest)
	{
		printf("Invalid file\n");
		return;
	}

	// going to the end to know how much allocate
	if(fseek(src, 0L, SEEK_END) == 0)
	{
		long bufsize = ftell(src);

		rewind(src);

		char *buf = malloc(sizeof(char) * bufsize);

		fread(buf, sizeof(char), bufsize, src);
		fwrite(buf, sizeof(char), bufsize, dest);
	}
	else printf("some error happened, report this\n");

	fclose(src);
	fclose(dest);
}

void printFilesInFolder(char* path)
{
	DIR* dir;
	struct dirent* entry;

    if ((dir = opendir(path)))
	{
        while ((entry = readdir(dir)))
		{
 			if (entry->d_name[0] != '.') printf("%s\n", entry->d_name);
		}
		closedir(dir);
	}

    else if(!mkdir(path, 0700)) printFilesInFolder(path);
}

void backup(char *path, char *file)
{// change the whole thing, too much string handling for too little
	char date[16];
	struct tm* ts;
	time_t now = time(NULL);
	ts = localtime(&now);
	strftime(date, 16, "\040%d-%m-%y\040%H:%M", ts);

	char bak[PATH_SIZE], bakfile[PATH_SIZE];
	char* lastElementCh = (char*) memccpy(bak, path, '\0', PATH_SIZE) - 1;
	lastElementCh = (char*) memccpy(lastElementCh, ".bck/", '\0', PATH_SIZE) - 1;

	lastElementCh = (char*) memccpy(bakfile, bak, '\0', PATH_SIZE) - 1;
	lastElementCh = (char*) memccpy(lastElementCh, file, '\0', PATH_SIZE) - 1;
	lastElementCh = (char*) memccpy(lastElementCh, date, '\0', PATH_SIZE);

	char source[PATH_SIZE];
	lastElementCh = (char*) memccpy(source, path, '\0', PATH_SIZE) - 1;
	memccpy(lastElementCh, file, '\0', PATH_SIZE);

	if(!mkdir(bak, 0700)) backup(path, file);

	copyContent(bakfile, source);
}

void restore(char *path, char *file)
{
	DIR* dir;
	struct dirent* entry;
	char files[10][PATH_SIZE];
	unsigned int index = 1;
	char* lastElementCh;

    if ((dir = opendir(path)))
	{
        while ((entry = readdir(dir)))
		{
			if (!memcmp(entry->d_name, file, strlen(file)))
			{
				printf("%d) %s\n", index, entry->d_name);
				lastElementCh = (char*) memccpy(files[index++], path, '\0', PATH_SIZE) - 1;
				memccpy(lastElementCh, entry->d_name, '\0', FILE_SIZE);
			}
		}
		closedir(dir);

		if(index == 1)
		{
			printf("you have no backups for this file\n");
			return;
		}

		if(index > 2)
		{
			printf("select the backup through the index number: ");
			scanf(" %u", &index);
		}

		lastElementCh = (char*) memccpy(files[0], path, '\0', PATH_SIZE) - 6;
		memccpy(lastElementCh, file, '\0', PATH_SIZE);

		copyContent(files[0], files[index]);
	}

	else
	{
		if(!mkdir(path, 0700)) return;

		else printf("you have no backups for this file\n");
	}
}

void deleteFile(char *path, char *file)
{
	char toDelete[PATH_SIZE];
	char* lastElementCh;
	lastElementCh = (char*) memccpy(toDelete, path, '\0', PATH_SIZE) - 1;
	memccpy(lastElementCh, file, '\0', PATH_SIZE);

	if (!remove(toDelete))
	{
		printf("\"%s\" deleted\n", file);
	}
	else
	{
		printf("File data not found\n");
		exit(1);
	}
}

void clean_stdin()
{
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

void mainMenu(char* path, char const* file)
{
	List* list = initList(path, file);

	char code[CODE_SIZE];
	char filename[FILE_SIZE];
	char option;
	float value;
	int quantity;
	int failed;
	welcomeMessage();

	while(list)
	{
		failed = 1;// gonna be defined to 1 in each iteration to know if a entry was valid or not

		printf("T)rade  L)ist papers  P)retend trade  D)elete paper  Q)uit  S)ave\n");

		scanf(" %c", &option);
		clean_stdin();

		if (option > 64 && option < 91) option += 32;

		if(option == 't')
		{
			printf("Code: ");
			scanf(" %s", code);

			printf("use a positive value for buy or negative to sell\n");
			printf("Quantity: ");
			scanf(" %i", &quantity);	

			printf("Unitary value: ");
			scanf(" %f", &value);

			printf("\n");

			Paper* paper = searchPaper(list->start, code);
			
			if (paper) failed = trade(list, paper, value, quantity);

			else failed = addPaper(list, createPaper(code, value, quantity)); 
		}

		else if (option == 'd')
		{
			printf("Code: ");
			scanf(" %s", code);
			printf("\n");
			failed = deletePaper(list, code);
		}

		else if (option == 's')
		{
			printFilesInFolder(path);
			printf("save to: ");
			scanf(" %s", filename);
			memccpy(path + strlen(path), filename, '\0', PATH_SIZE);

			saveList(list, path);
			exit(0);
		}

		else if (option == 'l')
		{
			listPapers(list->start);
			failed = 0;
		}

		else if (option == 'p')
		{
			printf("code: ");
			scanf(" %s", code);

			Paper* paper = searchPaper(list->start, code);

			if(paper)
			{
				printf("Quantity: ");
				scanf(" %d", &quantity);

				printf("value by unit: ");
				scanf(" %f", &value);

				failed = 0;
				simulateTrade(paper, value, quantity);
			}
		}

		else if (option == 'q') exit(0);

		if (failed) printf("\nInvalid entry\n");
	}	
}
