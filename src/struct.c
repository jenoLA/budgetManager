#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "struct.h"

void setWeek(char* date)
{
	time_t now = time(NULL);;
	struct tm* ts;
	ts = localtime(&now);

	strftime(date, 15, "%d/%m/%y %a", ts);
}

List* readList(char const* path)
{
	FILE* pf;
	List* list = malloc(sizeof(List));
	pf = fopen(path, "r");
	
	if (!pf)
    {    
		printf("\nfile data not found\n");
		exit(1);
	}

	if (!fscanf(pf, "\"size\": %i\n", &(list->size)))
	{
		printf("\nfile data invalid\n");
		exit(1);
	}

	fscanf(pf, "\"totalValue\": %i\n", &(list->totalValue));
	fscanf(pf, "\"earned\": %i\n", &(list->earned));

	fscanf(pf, "\n");
	list->start = malloc(sizeof(Paper));
	Paper** currentPaper = &list->start;
	for (int i = 0; i < list->size; ++i)
	{
		currentPaper = malloc(sizeof(Paper));
		fscanf(pf, "\"paper\": \"%s\"\n", (*currentPaper)->code);
		fscanf(pf, "\t\"buyValue\": %f\n", (*currentPaper)->buyValue);
		fscanf(pf, "\t\"earned\": %f\n", (*currentPaper)->earned);
		fscanf(pf, "\t\"quantity\": %i\n", &(*currentPaper)->quantity);
		fscanf(pf, "\t\"actualQuantity\": %i\n", &(*currentPaper)->actualQuantity);
		fscanf(pf, "\t\"dayOf\": %[^\n]\n", &(*currentPaper)->dayOf);

		if ((*currentPaper)->quantity != (*currentPaper)->actualQuantity)
			fscanf(pf, "\t\t\t\"selled\": %[^\n]\n", &(*currentPaper)->selled);

		currentPaper = &(*currentPaper)->next;
	}

	currentPaper = NULL;
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

	fprintf(pf, "\"size\": %i\n", list->size);
	fprintf(pf, "\"totalValue\": %i\n", list->totalValue);
	fprintf(pf, "\"earned\": %i\n", list->earned);
	fprintf(pf, "\n");

	Paper** currentPaper = &list->start;
	for (int i = 0; i < list->size; ++i)
	{
		fprintf(pf, "\"paper\": \"%s\"\n", (*currentPaper)->code);
		fprintf(pf, "\t\"buyValue\": %0.2f\n", (*currentPaper)->buyValue);
		fprintf(pf, "\t\"earned\": %0.2f\n", (*currentPaper)->earned);	
		fprintf(pf, "\t\"quantity\": %i\n", (*currentPaper)->quantity);
		fprintf(pf, "\t\"actualQuantity\": %i\n", (*currentPaper)->actualQuantity);
		fprintf(pf, "\t\"dayOf\": %s\n", (*currentPaper)->dayOf);

		if ((*currentPaper)->quantity != (*currentPaper)->actualQuantity)
			fprintf(pf, "\t\"selled\": %s\n", (*currentPaper)->selled);

		fprintf(pf, "\n");

		currentPaper = &(*currentPaper)->next;
	}

	fclose(pf);
}
