#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "../include/commands.h"
#include "../include/struct.h"
#include "../include/budget.h"
#include "../include/paper.h"

#define HOME getenv("HOME")

enum cli{opt1_ = 1, file_, opt2_, budgetName_, opt3_, code_, value_, quantity_};

enum arr{hipen, character};
// handle the options
int main(int argc, char const *argv[])
{
	char path[40];
	strncpy(path, HOME, 20);
	strncat(path, "/.bgtManager/", 14);

	if (argc == 1)
		mainMenu(path, NULL);

	else if (argv[opt1_][hipen] == '-')
	{
		if (argv[opt1_][character] == 'l')
		{
			printFilesInFolder(path);
			exit(0);
		}

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
						Budget* budget = searchBudget (list->start, argv [budgetName_]);

						if (!budget)
						{
							printf("\e[31m");
							printf("\nInvalid budget\n");
							exit(1);
						}

						else if (argc == 5)
							success = paperMenu(budget);

						else if (argv [opt3_][character] == 'l')
						{
							listPapers(budget->start);
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
						
							char code[6];
							strncpy(code, argv [code_], codeSize);
	
							for (int i = 0; i < codeSize; ++i)
								code[i] = toupper(code[i]);
							
							if (argv [opt3_][character] == 'd')
								success = deletePaper(budget, code);

							else if (argc == 9)
							{
								Paper* paper;
								float value;
								sscanf(argv [value_], "%f", &value);
								
								int quantity;
								sscanf(argv [quantity_], "%i", &quantity);

								if (argv [opt3_][character] == 'b')
								{
									paper = searchPaper(budget->start, code);
									
									if (paper)
										success = updatePaperBuy(budget, paper, value, quantity);

									else
										success = addPaper(budget, createPaper(code,  value, quantity));

								}
								
								else if (argv [opt3_][character] == 's')
								{
									paper = searchPaper(budget->start, code);
									
									if (paper)
										success = updatePaperSell(budget, paper, value, quantity);

								}
								// put option print too
								else if (argv [opt3_][character] == '-')
								{
									paper = searchPaper(budget->start, code);
									
									if (paper)
										simulateSell(paper, value, quantity);
							
									exit(0);
								}
							}
						}
					}

					else if (argv[opt2_][character] == 'd')
						success = deleteBudget (list, argv [budgetName_]);

					else if (argv [opt2_][character] == 'n')
						success = addBudget(list, initBudget (argv [budgetName_]));

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
				int status = remove(strncat(path, file, 60));
				if (status)
					printf("\n%s deleted\n", file);

				else
					printf("\n%s not found\n", file);

				exit(0);
			}

			else if (argv [opt1_][character] == 'b')
			{
				char bak[sizeStr];
				strncpy(bak, ".", 2);
				strncat(bak, file, sizeStr);
				saveList(list, strncat(path, bak, 60));

				exit(0);
			}

			else if (argv [opt1_][character] == 'r')
			{
				char bak[sizeStr];
				strncpy(bak, ".", 2);
				strncat(bak, file, sizeStr);
				list = initList(path, bak);
				saveList(list, strncat(path, file, 60));

				printf("%s restored!\n", file);
				exit(0);
			}
		}
	}

	// mini help message
	printf("-h or --help:\n");
	
	printf("\n-f <data-file>          ~ enter or get data of a data file ~");
	printf("\n-b <data-file>          ~ backup of the data file ~");
	printf("\n-r <data-file>          ~ restore a data file from backup ~");
	printf("\n-l                      ~ list elements ~");
	
	printf("\n-B                      ~ enter in the budget, also used combinated ~");
	printf("\n-d                      ~ delete a budget or paper ~");
	
	printf("\n-n                      ~ declares a new budget ~");
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

	return 0;
}
