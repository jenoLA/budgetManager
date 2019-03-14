#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/struct.h"

void setWeek(char* date)
{
	time_t now = time(NULL);;
	struct tm* ts;
	ts = localtime(&now);

	strftime(date, 15, "%d:%m:%y %a", ts);
}

List* readList(char const *path)
{
	FILE* pf;
	List* list = malloc(sizeof(List));
	pf = fopen(path, "r");
	if (pf == NULL)
	{
		printf("file data not found or invalid\n");
		exit(1);
	}
	fscanf(pf, "\"list\"\n");
	fscanf(pf, "\"size\": %i\n", &(list->size));
	Budget* currentBudget = malloc(sizeof(Budget));
	Paper* currentPaper;
	for (int i = 0; i < list->size; ++i)
	{
		currentBudget->next = malloc(sizeof(Budget));
		fscanf(pf, "\n\t\"budget\": %s\n", currentBudget->next->name);
		fscanf(pf, "\t\t\"size\": %i\n", &currentBudget->next->size);
		fscanf(pf, "\t\t\"totalValue\": %f\n", &currentBudget->next->totalValue);
		fscanf(pf, "\t\t\"earned\": %f\n", &currentBudget->next->earned);

		currentPaper = malloc(sizeof(Paper));
		for (int j = 0; j < currentBudget->next->size; ++j)
		{
			currentPaper->next = malloc(sizeof(Paper));
			fscanf(pf, "\t\t\"paper\": %s\n", currentPaper->next->code);
			fscanf(pf, "\t\t\t\"bValue\": %f\n", &currentPaper->next->bValue);
			fscanf(pf, "\t\t\t\"earned\": %f\n", &currentPaper->next->earned);
			fscanf(pf, "\t\t\t\"quantity\": %i\n", &currentPaper->next->quantity);
			fscanf(pf, "\t\t\t\"actualQuantity\": %i\n", &currentPaper->next->actualQuantity);

			// for the first paper in the budget
			if (j == 0)
			{
				currentBudget->next->start = currentPaper->next;
				currentPaper = currentBudget->next->start;
			}
			else
				currentPaper = currentPaper->next;
		}

		// for the first budget in the list
		if (i == 0)
		{
			list->start = currentBudget->next;
			currentBudget = list->start;
		}
		else
			currentBudget = currentBudget->next;
	}
	fclose(pf);
	return list;
}

void saveList(List* list, char* path)
{
	FILE* pf;
	pf = fopen(path, "w+");
	if (pf == NULL)
	{
		printf("something has gone wrong\n");
	}
	fprintf(pf, "\"list\"\n");
	fprintf(pf, "\"size\": %i\n", list->size);
	Budget* currentBudget = list->start;
	while(currentBudget != NULL)
	{
		fprintf(pf, "\n\t\"budget\": %s\n", currentBudget->name);
		fprintf(pf, "\t\t\"size\": %i\n", currentBudget->size);
		fprintf(pf, "\t\t\"totalValue\": %0.2f\n", currentBudget->totalValue);
		fprintf(pf, "\t\t\"earned\": %0.2f\n", currentBudget->earned);
		Paper* currentPaper = currentBudget->start;

		while(currentPaper != NULL)
		{
			fprintf(pf, "\t\t\"paper\": %s\n", currentPaper->code);
			fprintf(pf, "\t\t\t\"bValue\": %0.2f\n", currentPaper->bValue);
			fprintf(pf, "\t\t\t\"earned\": %0.2f\n", currentPaper->earned);	
			fprintf(pf, "\t\t\t\"quantity\": %i\n", currentPaper->quantity);
			fprintf(pf, "\t\t\t\"actualQuantity\": %i\n", currentPaper->actualQuantity);
			currentPaper = currentPaper->next;
		}

		currentBudget = currentBudget->next;
	}
	fclose(pf);
	printf("\nsaved!!\n\n");
}
