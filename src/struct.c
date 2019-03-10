#include "../include/struct.h"

List* readList(char* path)
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
		fscanf(pf, "\t\"budget\": %s\n", currentBudget->next->name);
		fscanf(pf, "\t\t\"size\": %i\n", &(currentBudget->next->size));
		fscanf(pf, "\t\t\"totalValue\": %f\n", &(currentBudget->next->totalValue));
		fscanf(pf, "\t\t\"earned\": %f\n", &(currentBudget->next->earned));

		currentPaper = malloc(sizeof(Paper));
		for (int j = 0; j < currentBudget->next->size; ++j)
		{
			currentPaper->next = malloc(sizeof(Paper));
			fscanf(pf, "    \"paper\": %s\n", currentPaper->next->code);
			fscanf(pf, "      \"initialValue\": %f\n", &(currentPaper->next->initialValue));
			fscanf(pf, "      \"earned\": %f\n", &(currentPaper->next->earned));
			fscanf(pf, "      \"quantity\": %i\n", &(currentPaper->next->quantity));

			if (currentBudget->next->start == NULL)
			{// for the first paper in the budget
				currentBudget->next->start = currentPaper->next;
				currentPaper = currentBudget->next->start;
			}
			else
				currentPaper = currentPaper->next;
		}
		fscanf(pf, "\n");
		if (i == 0)
		{// for the first budget in the list
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
		fprintf(pf, "\t\"budget\": %s\n", currentBudget->name);
		fprintf(pf, "\t\t\"size\": %i\n", currentBudget->size);
		fprintf(pf, "\t\t\"totalValue\": %0.2f\n", currentBudget->totalValue);
		fprintf(pf, "\t\t\"earned\": %0.2f\n", currentBudget->earned);
		Paper* currentPaper = currentBudget->start;

		while(currentPaper != NULL)
		{
			fprintf(pf, "\t\t\"paper\": %s\n", currentPaper->code);
			fprintf(pf, "\t\t\t\"initialValue\": %0.2f\n", currentPaper->initialValue);
			fprintf(pf, "\t\t\t\"earned\": %0.2f\n", currentPaper->earned);	
			fprintf(pf, "\t\t\t\"quantity\": %i\n", currentPaper->quantity);
			currentPaper = currentPaper->next;
		}
		fprintf(pf, "\n");
		currentBudget = currentBudget->next;
	}
	fclose(pf);
	printf("\nsaved!!\n\n");
}
