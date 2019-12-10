#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "commands.h"
#include "struct.h"
#include "paper.h"

#define HOME getenv("HOME")

enum cli{opt1_ = 1, opt2_, code_, value_, quantity_};

int main(const int argc, char const *argv[])
{
	char path[PATH_SIZE];
	char file[FILE_SIZE];
	memccpy(memccpy(path, HOME, '\0', PATH_SIZE) - 1, "/.bgtManager/", '\0', PATH_SIZE);

	if (argc == 1) mainMenu(path, NULL);

	else if(!strcmp(argv[opt1_], "-h") || !strcmp(argv[opt1_], "--help"))
	{
		helpMessage();
	}
	else if(!strcmp(argv[opt1_], "-l") || !strcmp(argv[opt1_], "--list"))
	{
		printFilesInFolder(path);
	}

	else if(argv[opt1_][0] != '-')
	{
		memccpy(file, argv[opt1_], '\0', FILE_SIZE);
		int failed = 1;

		if(argc == 2) mainMenu(path, file);

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
			char code[CODE_SIZE];
			memccpy(code, argv[code_], '\0', CODE_SIZE);

			int quantity = atoi(argv[quantity_]);
			float value = atof(argv[value_]);
			Paper* paper = searchPaper(list->start, code);

			if(paper)
			{
				if(!strcmp(argv[opt2_], "-t") || !strcmp(argv[opt2_], "--trade"))
				{
					failed = trade(list, paper, value, quantity);
				}
				else if(!strcmp(argv[opt2_], "-T") || !strcmp(argv[opt2_], "--simulate-trade"))
				{
					simulateTrade(paper, value, quantity);
					exit(0);
				}
			}

			else if(!strcmp(argv[opt2_], "-t") || !strcmp(argv[opt2_], "--trade"))
				failed = addPaper(list, createPaper(code, value, quantity));

		}

		if(!failed)
		{
			memccpy(path + strlen(path), file, '\0', FILE_SIZE);
			saveList(list, path);
		}

		else
		{
			printf("invalid entry\n");
			exit(1);
		}
	}

	else if (argc == 3)
	{
		memccpy(file, argv[opt2_], '\0', FILE_SIZE);

		if(!strcmp(argv[opt1_], "-r") || !strcmp(argv[opt1_], "--restore"))
		{
			memccpy(path + strlen(path), ".bck/", '\0', FILE_SIZE);
			restore(path, file);
		}
		else if(!strcmp(argv[opt1_], "-b") || !strcmp(argv[opt1_], "--backup"))
			backup(path, file);

		else if(!strcmp(argv[opt1_], "-d") || !strcmp(argv[opt1_], "--delete"))
			deleteFile(path, file);

	}
}
