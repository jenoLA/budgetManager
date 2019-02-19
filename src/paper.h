#include <stdlib.h>
#include <stdio.h>

typedef struct paper
{
	char* code;
	float initalValue;
	float finalValue;
	int totalTime; // on the time being till inplementation of time appopriatly
	struct paper* next
} Paper;

createPaper(Budget* budget, char* code, float initialValue);

searchpaper(char* code);

updatePaper(Paper paper, float finalValue, int totalTime);

