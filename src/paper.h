
typedef struct paper
{
	char* code;
	float initalValue;
	float finalValue;
	int totalTime; // on the time being till inplementation of time appopriatly
	struct paper* next;
} Paper;

Paper* createPaper(Budget* budget, char* code, float initialValue);

Paper* searchpaper(char* code);

void appendPaper(Budget budget, Paper paper);

void deletePaper(Budget budget, char* code);

void paperLoop(Budget budget);

void updatePaper(Paper paper, float finalValue, int totalTime);
