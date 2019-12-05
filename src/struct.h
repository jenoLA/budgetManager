#pragma once

typedef struct paper_t
{
	char code[7];
	float averageValue;
	float earned;
	unsigned int quantity;
	unsigned int actualQuantity;
	char dayOfBuy[13];
	char dayOfSell[13];
	struct paper_t* next;
} Paper;

typedef struct list_t
{
	Paper* start;
	unsigned int size;
	float totalValue;
	float earned;
	char lastModified[13];
} List;

//return a string in the format dd/mm/yy DoW
void setWeek(char* date);

List* readList(char const *path);

void saveList(List* list, char const* path);
