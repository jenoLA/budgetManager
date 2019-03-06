#include <stdio.h>
#include "../include/struct.h"

List* readList(char* path);

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
		fprintf(pf, "  \"budget\": \"%s\",\n", current->name);
		fprintf(pf, "    \"size\": %i,\n", current->size);
		Paper* pcurrent = current->start;
		while(pcurrent != NULL)
		{
			fprintf(pf, "    \"paper\": \"%s\",\n", pcurrent->code);
			fprintf(pf, "      \"initialValue\": %0.2f,\n", pcurrent->initialValue);
			fprintf(pf, "      \"selled\": %i,\n", pcurrent->isSelled);
			if (pcurrent->isSelled == 1)
			{
				fprintf(pf, "      \"finalValue\": %0.2f,\n", pcurrent->finalValue);
			}
			fprintf(pf, "      \"quantity\": %i,\n", pcurrent->quantity);
			pcurrent = pcurrent->next;
		}
		fprintf(pf, "\n");
		current = current->next;
	}
	fclose(pf);
	printf("\nsaved!!\n\n");
}