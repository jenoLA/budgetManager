#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "commands.h"
#include "struct.h"
#include "paper.h"

#define HOME getenv("HOME")

void backup(char *path, char *file)
{
	char bak[60];
	strncpy(bak, ".", 2);
	strncat(bak, file, 60);
	List* list = initList(path, file);
	if(list->start)
	{
		saveList(list, strncat(path, bak, 60));
		exit(0);
	}

	printf("invalid entry\n");
	exit(1);
}

// improve and verify if it is valid
void restore(char *path, char *file)
{
	char bak[60];
	strncpy(bak, ".", 2);
	strncat(bak, file, 60);
	List* list = initList(path, bak);
	saveList(list, strncat(path, file, 60));

	printf("%s restored!\n", file);
	exit(0);
}

void deleteFile(char *path, char *file)
{
	if (!remove(strncat(path, file, 60)))
		printf("\"%s\" deleted\n", file);

	else
	{
		printf("File data not found\n");
		exit(1);
	}
}

enum cli{opt1_ = 1, opt2_, code_, value_, quantity_};

int main(const int argc, char const *argv[])
{
	char path[60];
	char file[21];
	strncpy(path, HOME, sizeof(HOME) / sizeof(char) + 3);
	strncat(path, "/.bgtManager/", 14);

	if (argc == 1)
		mainMenu(path, NULL);

	else if(!strcmp(argv[opt1_], "-l") || !strcmp(argv[opt1_], "--list"))
		printFilesInFolder(path);

	else if(argv[opt1_][0] != '-')
	{
		strncpy(file, argv[opt1_], 21);
		int failed = 1;

		if(argc == 2)
			mainMenu(path, file);

		List* list = initList(path, file);

		if(!strcmp(argv[opt2_], "-l") || !strcmp(argv[opt2_], "--list"))
		{
			listPapers(list->start);
			exit(0);
		}

		else if(argc == 4)
		{
			if(!strcmp(argv[opt2_], "-d") || !strcmp(argv[opt2_], "--delete"))
			{
				failed = deletePaper(list, (char*) argv[code_]);
			}
		}

		else if(argc == 6)
		{
			char code[7];
			strncpy(code, argv[code_], 7);

			int quantity = atoi(argv[quantity_]);
			float value = atof(argv[value_]);
			Paper* paper = searchPaper(list->start, code);

			if(paper)
			{
				if(!strcmp(argv[opt2_], "-b") || !strcmp(argv[opt2_], "--buy"))
					failed = buyPaper(list, paper, value, quantity);

				else if(!strcmp(argv[opt2_], "-s") || !strcmp(argv[opt2_], "--sell"))
					failed = sellPaper(list, paper, value, quantity);

				else if(!strcmp(argv[opt2_], "-B") || !strcmp(argv[opt2_], "--simulate-buy"))
					simulateBuy(paper, value, quantity);

				else if(!strcmp(argv[opt2_], "-S") || !strcmp(argv[opt2_], "--simulate-sell"))
					simulateSell(paper, value, quantity);

			}

			if(!strcmp(argv[opt2_], "-b") || !strcmp(argv[opt2_], "--buy"))
				failed = addPaper(list, createPaper(code, value, quantity));

		}

		if(!failed)
			saveList(list, strncat(path, file, 21));

		else
		{
			printf("invalid entry\n");
			exit(1);
		}
	}

	else if (argc == 3)
	{
		strncpy(file, argv[opt2_], 21);

		if(!strcmp(argv[opt1_], "-r") || !strcmp(argv[opt1_], "--restore"))
			restore(path, file);

		else if(!strcmp(argv[opt1_], "-b") || !strcmp(argv[opt1_], "--backup"))
			backup(path, file);

		else if(!strcmp(argv[opt1_], "-d") || !strcmp(argv[opt1_], "--delete"))
			deleteFile(path, file);
	
	}
}
