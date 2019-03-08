#include <stdio.h>
#include <stdlib.h>
#include "../include/struct.h"

List* readList(char* path)
{
	FILE* pf;
	List* list = malloc(sizeof(List));
	pf = fopen(path, "r");
	if (pf == NULL)
	{
		printf("file data not found\n");
		exit(1);
	}
	fscanf(pf, "\"list\"\n");
	fscanf(pf, "\"size\": %i\n", &(list->size));
	Budget* current = malloc(sizeof(Budget));
	Paper* pcurrent;
	for (int i = 0; i < list->size; ++i)
	{
		current->next = malloc(sizeof(Budget));
		fscanf(pf, "  \"budget\": %s\n", &(current->next->name));
		fscanf(pf, "    \"size\": %i\n", &(current->next->size));

		Paper* pcurrent = malloc(sizeof(Paper));
		for (int j = 0; j < current->next->size; ++j)
		{
			pcurrent->next = malloc(sizeof(Paper));
			fscanf(pf, "    \"paper\": %s\n", &(pcurrent->next->code));
			fscanf(pf, "      \"initialValue\": %f\n", &(pcurrent->next->initialValue));
			fscanf(pf, "      \"selled\": %i\n", &(pcurrent->next->isSelled));
			if (pcurrent->next->isSelled == 1)
			{
				fscanf(pf, "      \"finalValue\": %f\n", &(pcurrent->next->finalValue));
			}
			fscanf(pf, "      \"quantity\": %i\n", &(pcurrent->next->quantity));
			
			if (current->next->start == NULL)
			{// for the first paper in the budget
				current->next->start = pcurrent->next;
				pcurrent = current->next->start;
			}
			else
				pcurrent = pcurrent->next;
		}
		fscanf(pf, "\n");
		if (i == 0)
		{// for the first budget in the list
			list->start = current->next;
			current = list->start;
		}
		else
			current = current->next;
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
	Budget* current = list->start;
	while(current != NULL)
	{
		fprintf(pf, "  \"budget\": %s\n", current->name);
		fprintf(pf, "    \"size\": %i\n", current->size);
		Paper* pcurrent = current->start;
		while(pcurrent != NULL)
		{
			fprintf(pf, "    \"paper\": %s\n", pcurrent->code);
			fprintf(pf, "      \"initialValue\": %0.2f\n", pcurrent->initialValue);
			fprintf(pf, "      \"selled\": %i\n", pcurrent->isSelled);
			if (pcurrent->isSelled == 1)
			{
				fprintf(pf, "      \"finalValue\": %0.2f\n", pcurrent->finalValue);
			}
			fprintf(pf, "      \"quantity\": %i\n", pcurrent->quantity);
			pcurrent = pcurrent->next;
		}
		fprintf(pf, "\n");
		current = current->next;
	}
	fclose(pf);
	printf("\nsaved!!\n\n");
}