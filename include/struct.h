#ifndef STRUCT_H
#define STRUCT_H

typedef struct paper_t
{
	char code[6];
	float bValue;
	int quantity;
	float earned;
	int actualQuantity;
	char dayOf[sizeof("dd:mm:yy sun")];
	struct paper_t* next;
} Paper;

typedef struct budget_t
{
	Paper* start;
	char name[20];
	int size;
	float totalValue;
	float earned;
	char lastModified[sizeof("dd:mm:yy sun")];
	struct budget_t* next;
} Budget;

typedef struct
{
	Budget* start;
	int size;
} List;

//return a string in the format dd:mm:yyyy
void setWeek(char* date);
//return the one readed from the data file on the path, if exists
List* readList(char const *path);

//save the state of the list in a data file saved on the path
void saveList(List* list, char* path);


#endif
