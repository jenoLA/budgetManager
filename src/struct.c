#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "struct.h"

void setWeek(char* date)
{
	struct tm* ts;
	time_t now = time(NULL);
	ts = localtime(&now);

	strftime(date, 13, "%d/%m/%y %a", ts);
}

List* readList(char const* path)
{
	FILE* pf;
	List* list = malloc(sizeof(List));
	pf = fopen(path, "r");
	
	if (!pf)
    {    
		printf("File data not found\n");
		exit(1);
	}

	if (!fscanf(pf, "size: %i\n", &(list->size)))
	{
		printf("File data invalid\n");
		exit(1);
	}

	fscanf(pf, "totalValue: %f\n", &(list->totalValue));

	fscanf(pf, "earned: %f\n", &(list->earned));
	fscanf(pf, "\n");

	Paper** paper = &list->start;
	for (int i = 0; i < list->size; i++)
	{
		*paper = malloc(sizeof(Paper));
		fscanf(pf, "paper: %s\n", (*paper)->code);
		fscanf(pf, " buyValue: %f\n", &(*paper)->buyValue);
		fscanf(pf, " earned: %f\n", &(*paper)->earned);
		fscanf(pf, " quantity: %u\n", &(*paper)->quantity);
		fscanf(pf, " actualQuantity: %u\n", &(*paper)->actualQuantity);
		fscanf(pf, " dayOfBuy: \"%[^\"]\"\n", (*paper)->dayOfBuy);

		if ((*paper)->quantity != (*paper)->actualQuantity)
		{
			fscanf(pf, " dayOfSell: \"%[^\"]\"\n", (*paper)->dayOfSell);
		}
		paper = &(*paper)->next;
	}

	fclose(pf);
	return list;
}

void saveList(List* list, char const* path)
{
	FILE* pf;
	pf = fopen(path, "w+");
	
	if (!pf)
	{
		printf("\ninvalid directory\n");
		exit(1);
	}

	fprintf(pf, "size: %i\n", list->size);
	fprintf(pf, "totalValue: %f\n", list->totalValue);
	fprintf(pf, "earned: %f\n", list->earned);
	fprintf(pf, "\n");

	Paper** paper = &list->start;
	for (int i = 0; i < list->size; ++i)
	{
		fprintf(pf, "paper: %s\n", (*paper)->code);
		fprintf(pf, " buyValue: %f\n", (*paper)->buyValue);
		fprintf(pf, " earned: %f\n", (*paper)->earned);	
		fprintf(pf, " quantity: %u\n", (*paper)->quantity);
		fprintf(pf, " actualQuantity: %u\n", (*paper)->actualQuantity);
		fprintf(pf, " dayOfBuy: \"%s\"\n", (*paper)->dayOfBuy);

		if ((*paper)->quantity != (*paper)->actualQuantity)
		{
			fprintf(pf, " dayOfSell: \"%s\"\n", (*paper)->dayOfSell);
		}
		paper = &(*paper)->next;
	}

	fclose(pf);
}
