#ifndef STRUCT_H
#define STRUCT_H


typedef struct paper_t
{
	char code[6];
	float initialValue;
	float finalValue;
	int quantity;
	int isSelled;
	struct paper_t* next;
} Paper;

typedef struct budget_t
{
	Paper* start;
	char name[20];
	int size;
	struct budget_t* next;
} Budget;

typedef struct
{
	Budget* start;
	int size;
} List;

void readList();

void saveList(List* list, char* path);


#endif
