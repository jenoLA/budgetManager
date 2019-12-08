#pragma once
#define PATH_SIZE 81
#define FILE_SIZE 21
#define CODE_SIZE 7
#define DATE_SIZE 13

typedef struct paper_t
{
	char code[CODE_SIZE];
	float averageValue;
	float earned;
	unsigned int quantity;
	unsigned int actualQuantity;
	char dayOfBuy[DATE_SIZE];
	char dayOfSell[DATE_SIZE];
	struct paper_t* next;
} Paper;

typedef struct list_t
{
	Paper* start;
	unsigned int size;
	float totalValue;
	float earned;
	char lastModified[DATE_SIZE];
} List;

//return a string in the format dd/mm/yy DoW
void setWeek(char* date);

List* readList(char const *path);

void saveList(List* list, char const* path);
