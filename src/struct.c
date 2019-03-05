#include <stdio.h>
#include "../include/struct.h"

void readList(char* path);

void saveList(List* list)
{
	Budget* current = list->start;
// using union here seems good
	while(current != NULL)
	{
		Paper* pcurrent = current->start;
		printf("\"budget\": \"%s\"\n", current);
		printf("  \"size\": \"%i\"\n", current->size);
		while(pcurrent != NULL)
		{
			printf("  \"paper\": \"%s\"\n", pcurrent->code);
			printf("    \"initialValue\": \"%f\"\n", pcurrent->initialValue);
			if (pcurrent->isSelled == 1)
			{
				printf("    \"finalValue\": \"%f\"\n", pcurrent->finalValue);
			}
			printf("    \"quantity\": \"%i\"\n", pcurrent->quantity);
			pcurrent = pcurrent->next;
		}
		printf("\n");
		current = current->next;
	}
}