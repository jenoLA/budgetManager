#ifndef PAPER_H
#define PAPER_H


typedef struct
{
	Budget* start;
	int size;
} List;

typedef struct budget_t
{
	Paper* start;
	char name[20];
	int size;
	struct budget_t* next;
} Budget;

typedef struct paper_t
{
	char* code;
	float initalValue;
	float finalValue;
	int totalTime; // from beginning till end
	struct paper_t* next;
} Paper;



#endif
