#ifndef STRUCT_H
#define STRUCT_H

typedef struct paper_t
{
	char code[7];
	float buyValue;
	int quantity;
	float earned;
	int actualQuantity;
	char dayOf[sizeof("dd:mm:yy sun")];
	char selled[sizeof("dd:mm:yy sun")];
	struct paper_t* next;
} Paper;

typedef struct list_t
{
	Paper* start;
	int size;
	float totalValue;
	float earned;
	char lastModified[sizeof("dd:mm:yy sun")];
} List;

//return a string in the format dd:mm:yyyy
void setWeek(char* date);

List* readList(char const *path);

void saveList(List* list, char const* path);


#endif
