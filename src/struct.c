#include <stdio.h>
#include <stdlib.h>
#include "../include/struct.h"

/*
	sketch:
	chaamr função initBudget
	depois addBudget
	depois fazer integração com os papeis
	create/add/updatePaper
*/
List* readList(char* path)
{
	FILE* pf;
	List* list = malloc(sizeof(List));
	pf = fopen(path, "r");
	if (pf == NULL)
	{
		printf("something has gone wrong\n");
	}
	fscanf(pf, "\"list\"\n");
	fscanf(pf, "\"size\": %i\n", &(list->size));
	list->start = malloc(sizeof(Budget)); //declaring to after delete
	Budget* current = list->start->next;// NULL by now
	Paper* pcurrent;
	for (int i = 0; i < list->size; ++i)
	{
		current = malloc(sizeof(Budget));
		fscanf(pf, "  \"budget\": %s\n", &(current->name));
		fscanf(pf, "    \"size\": %i\n", &(current->size));
		if (current->start == NULL)
		{
			current->start = malloc(sizeof(Paper));
			Paper* pcurrent = current->start->next;
		}
		for (int j = 0; j < current->size; ++j)
		{
			pcurrent = malloc(sizeof(Paper));
			fscanf(pf, "    \"paper\": %s\n", &(pcurrent->code));
			printf(" pcurrent code: %s\n", pcurrent->code);
			fscanf(pf, "      \"initialValue\": %f\n", &(pcurrent->initialValue));
			printf(" pcurrent initialValue: %f\n", pcurrent->initialValue);
			fscanf(pf, "      \"selled\": %i\n", &(pcurrent->isSelled));
			printf(" pcurrent selled: %i\n", pcurrent->isSelled);
			if (pcurrent->isSelled == 1)
			{
				fscanf(pf, "      \"finalValue\": %f\n", &(pcurrent->finalValue));
				printf(" pcurrent finalValue: %f\n", pcurrent->finalValue);
			}
			fscanf(pf, "      \"quantity\": %i\n", &(pcurrent->quantity));
			printf(" pcurrent quantity: %i\n", pcurrent->quantity);
			
			if (j == 0)
			{// for the first paper in the budget
				current->start = pcurrent;
				pcurrent = current->start->next;
			}
			else
				pcurrent = pcurrent->next;
		}
		if (i == 0)
		{// for the first budget in the list
			list->start = current;
		}
		fscanf(pf, "\n");
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