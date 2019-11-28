#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "paper.h"
#include "commands.h"

void welcomeMessage()
{
	printf("\e[0;m");
	printf("\n=========================");
	printf("\e[36m");
	printf(" Budget Manager ");
	printf("\e[m");
	printf("==========================\n\n");
}

void printFilesInFolder(char* path)
{
	DIR* dir;
	struct dirent* entry;

    if ((dir = opendir(path)))
	{
        printf("--------------------------[ data files ]-------------------------\n\n");

        while ((entry = readdir(dir)))
 			if (entry->d_name[0] != '.')
  				printf(">> %s\n", entry->d_name);

		closedir(dir);
		printf("\n");
	}

    else if(!mkdir(path, 0777)) printFilesInFolder(path);

    else
        printf("invalid folder\n");
}

void mainMenu(char* path, char const* file)
{
	List* list = initList(path, file);

	char code[7];
	char name[21];
	char option;
	int save;
	int failed;
	welcomeMessage();

	while(list)
	{
		failed = 1;// gonna be defined to 1 in each iteration to know if a entry was valid or not

		printf("\nN)ew paper  L)ist papers  U)pdate paper  P)retend action  D)elete paper  Q)uit  S)ave\n\n");

		scanf(" %c", &option);
		if (option > 64 && option < 91) option += 32;

		if (option == 'n')
		{
			char code[7];
			printf("\nCode: ");
			scanf(" %s", code);

			float value;
			printf("Unitary value: ");
			scanf(" %f", &value);

			int quantity;
			printf("Quantity: ");
			scanf(" %i", &quantity);
			printf("\n");
			failed = addPaper(list, createPaper(code, value, quantity));
		}

		else if(option == 'u')
		{
			char code[6];
			printf("\nCode: ");
			scanf(" %s", code);

			Paper* paper = searchPaper(list->start, code);
			
			if (paper)
			{
				float price; //for both situations
				float quantityMinus;
				char today[13];
				setWeek(today);
				
				if (!strcmp(paper->dayOfBuy, today))
					printf("\nif you sell this paper today, be ware of the tax\n");

				printf("\nQuantity selled: ");
				scanf(" %f", &quantityMinus);
				
				if (quantityMinus > 0)
				{
					printf("\nValue of the paper selled: ");
					scanf(" %f", &price); //sell price
					failed = updatePaperSell(list, paper, price, quantityMinus);
                }

                //buy part
                else
                {
                    float quantityPlus;
                    printf("\nQuantity brought: ");
                    scanf(" %f", &quantityPlus);

                    if (quantityPlus > 0)
                    {
                        printf("\nvalue by unit: ");
                        scanf(" %f", &price);
                        failed = updatePaperBuy(list, paper, price, quantityPlus);
                    }
                }
			}
		}	

		else if (option == 'd')
		{
			printf("\nCode: ");
			scanf(" %s", code);
			printf("\n");
			failed = deletePaper(list, code);
		}

		else if (option == 's')
		{
			printFilesInFolder(path);
			printf("Name to the new data file (20 caracters): ");
			scanf(" %s", name);
			printf("\n");
			
			saveList(list, strcat(path, name)); //sending directly
			exit(0);
		}
		
		else if (option == 'l')
		{
			listPapers(list->start);
			failed = 0;
		}

		else if (option == 'q') exit(0);

		else if (option == 'p')
		{
			printf("\ncode: ");
			scanf(" %s", code);
			
			Paper* paper = searchPaper(list->start, code);

			if(paper)
			{
				float quantityMinus, value;
				printf("\nQuantity selled: ");
				scanf(" %f", &quantityMinus);
				
				printf("Value of the paper selled: ");
				scanf(" %f", &value);
				
				simulateSell(paper, value, quantityMinus);
				failed = 0;
			}
		}

		if (failed)
			printf("\nInvalid entry\n");

	}	
}
