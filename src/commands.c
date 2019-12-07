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
        while ((entry = readdir(dir)))
		{
 			if (entry->d_name[0] != '.') printf("%s\n", entry->d_name);
		}
		closedir(dir);
	}

    else if(!mkdir(path, 0700)) printFilesInFolder(path);
}

void backup(char *path, char *file)
{
	char source_filename[PATH_SIZE];
	memccpy(memccpy(source_filename, path, '\0', PATH_SIZE) - 1, file, '\0', PATH_SIZE);

	FILE *src = fopen(source_filename, "r");
	if (!src)
	{
		printf("\"%s\" not found\n", file);
		exit(1);	
	}

	char date[16];
	struct tm* ts;
	time_t now = time(NULL);
	ts = localtime(&now);
	strftime(date, 16, "\040%d-%m-%y\040%H:%M", ts);

	char bak[PATH_SIZE], bakfile[PATH_SIZE];
	memccpy(memccpy(bak, path, '\0', PATH_SIZE) - 1, ".bck/", '\0', PATH_SIZE);
	memccpy(
			memccpy(
				memccpy(bakfile, bak, '\0', PATH_SIZE) - 1
				, file, '\0', PATH_SIZE) - 1
			, date, '\0', PATH_SIZE
	);

	printf("bakfile: %s\n", bakfile);
	FILE *bkp = fopen(bakfile, "w+");
	if(!bkp)
	{
		if(!mkdir(bak, 0700)) backup(path, file);

		else
		{
			printf("some error happened, please report\n");
			exit(1);
		}
	}

	char ch;
	while((ch = fgetc(src)) != EOF )
	{
		fputc(ch, bkp);
	}

	fclose(bkp);
	fclose(src);
}

// improve and verify if it is valid
void restore(char *path, char *file)
{
	// same as backup, also show possibility of show the contents, papers
//	char bak[PATH_SIZE];
//	strncpy(bak, ".", 2);
//	strncat(bak, file, PATH_SIZE);
//	List* list = initList(path, bak);
//	saveList(list, strncat(path, file, PATH_SIZE));
//
//	printf("%s restored!\n", file);
//	exit(0);
}

void deleteFile(char *path, char *file)
{
	char toDelete[PATH_SIZE];
	memccpy(memccpy(toDelete, path, '\0', PATH_SIZE) - 1, file, '\0', PATH_SIZE);
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
	int failed;
	welcomeMessage();

	while(list)
	{
		failed = 1;// gonna be defined to 1 in each iteration to know if a entry was valid or not

		printf("N)ew paper  L)ist papers  T)rade  P)retend action  D)elete paper  Q)uit  S)ave\n");

		scanf(" %c", &option);

		clean_stdin();
		if (option > 64 && option < 91) option += 32;

		if (option == 'n')
		{
			char code[7];
			printf("Code: ");
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

		else if(option == 't')
		{
			char code[6];
			printf("Code: ");
			scanf(" %s", code);

			Paper* paper = searchPaper(list->start, code);
			
			if (paper)
			{
				float value; //for both situations
				int quantity;

				printf("use a positive value for buy or negative to sell\n");
				printf("Quantity: ");
				scanf(" %d", &quantity);
				
				printf("value by unit: ");
				scanf(" %f", &value);

				trade(list, paper, value, quantity);
			}
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
			
			saveList(list, path); //sending directly
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
				float quantityMinus, value;
				printf("Quantity selled: ");
				scanf(" %f", &quantityMinus);
				
				printf("Value of the paper selled: ");
				scanf(" %f", &value);
				
				simulateSell(paper, value, quantityMinus);
				failed = 0;
			}
		}

		else if (option == 'q') exit(0);

		if (failed) printf("\nInvalid entry\n");
	}	
}
