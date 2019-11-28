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
	printf("\ninvalid entry\n");
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
	if (remove(strncat(path, file, 60)))
		printf("\n%s deleted\n", file);

	else
		printf("\n%s not found\n", file);

	exit(0);
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

	if(!strcmp(argv[opt1_], "-l") || !strcmp(argv[opt1_], "--list"))
		printFilesInFolder(path);

	if(!strcmp(argv[opt1_], "-r") || !strcmp(argv[opt1_], "--restore"))
		restore(path, file);

	if(!strcmp(argv[opt1_], "-b") || !strcmp(argv[opt1_], "--backup"))
		backup(path, file);

	if(!strcmp(argv[opt1_], "-d") || !strcmp(argv[opt1_], "--delete"))
		deleteFile(path, file);

	if(argv[opt1_][0] != '-')
	{
		mainMenu(path, argv[opt1_]);
	}
}
/*
		else if (argc > 2)
		{
			int sizeStr = strlen(argv [file_]);
			char file[sizeStr];
			strncpy(file, argv [file_], sizeStr);
			List* list = initList(path, file);

			if (argv[opt1_][character] == 'f')
			{
				if (argc == 3)
					mainMenu(path, file);

				else if (argc > 3)
				{
					int success;

					if (argv[opt2_][character] == 'l')
					{
						printBudgets(list->start);
						exit(0);
					}

					else if (argv[opt2_][character] == 'B')
					{
						Budget* list = searchBudget (list->start, argv [listName_]);

						if (!list)
						{
							printf("\e[31m");
							printf("\nInvalid list\n");
							exit(1);
						}

						else if (argc == 5)
							success = paperMenu(list);

						else if (argv [opt3_][character] == 'l')
						{
							listPapers(list->start);
							exit(0);
						}

						else if (argc > 6 && argc < 10)
						{

							int codeSize = strlen(argv [code_]);

							if (codeSize > 6)
							{
								printf("\e[33m");
								printf("\ncode too big to by a stock\n");
								exit(1);
							}

							char code[7];
							strncpy(code, argv [code_], codeSize);

							for (int i = 0; i < codeSize; ++i)
								code[i] = toupper(code[i]);
							
							if (argv [opt3_][character] == 'd')
								success = deletePaper(list, code);

							else if (argc == 9)
							{
								Paper* paper;
								float value;
								sscanf(argv [value_], "%f", &value);
								
								int quantity;
								sscanf(argv [quantity_], "%i", &quantity);

								if (argv [opt3_][character] == 'b')
								{
									paper = searchPaper(list->start, code);
									
									if (paper)
										success = updatePaperBuy(list, paper, value, quantity);

									else
										success = addPaper(list, createPaper(code,  value, quantity));

								}
								
								else if (argv [opt3_][character] == 's')
								{
									paper = searchPaper(list->start, code);
									
									if (paper)
										success = updatePaperSell(list, paper, value, quantity);

								}
								// put option print too
								else if (argv [opt3_][character] == '-')
								{
									paper = searchPaper(list->start, code);
									
									if (paper)
										simulateSell(paper, value, quantity);
							
									exit(0);
								}
							}
						}
					}

					else if (argv[opt2_][character] == 'd')
						success = deleteBudget (list, argv [listName_]);

					else if (argv [opt2_][character] == 'n')
						success = addBudget(list, initBudget (argv [listName_]));

					else
						printf("\nInvalid entry, verify your command\n");
					
					if (success)
						saveList (list, strncat(path, file, 60));
					
					// exit after do the job meant to be done
					exit(0);
				}
			}

			else if (argv[opt1_][character] == 'd')
			{
				
			}

			else if (argv [opt1_][character] == 'b')
			{
							}

			else if (argv [opt1_][character] == 'r')
			{
				
			}
		}
	}
	*//*
	// mini help message
	printf("-h or --help:\n");

	printf("\n-f <data-file>          ~ enter or get data of a data file ~");
	printf("\n-B <data-file>          ~ backup of the data file ~");
	printf("\n-r <data-file>          ~ restore a data file from backup ~");
	printf("\n-l                      ~ list elements ~");

	printf("\n-d                      ~ delete a list or paper ~");
    
	printf("\n-n                      ~ declares a new list ~");
	printf("\n-b                      ~ buy/create a paper, if exists modifies ~");
    
	printf("\n-s                      ~ sell the given paper ~");
	printf("\n--simul                 ~ simulate a sell ~\n");

	//  usage
	printf("\n======================== use cases ========================\n");
	printf("\n~ no arguments lead to the main menu ~\n");

	printf("\nbudgetManager -b <data-file>\n");
	printf("\nbudgetManager -r <data-file>\n");
	printf("\nbudgetManager -f <data-file> -l\n");

	printf("\nbudgetManager -f <data-file> -n <budget>\n");

	printf("\nbudgetManager -f <data-file> -B <budget> -l\n");

	printf("\nbudgetManager -f <data-file> -B <budget> -b <code> <value by unit> <quantity>\n");

	printf("\nbudgetManager -f <data-file> -B <budget> -- <code> <value by unit> <quantity>\n");
}
*/
