#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "struct.h"

void setWeek(char* date)
{
    struct tm* ts;
    time_t now = time(NULL);
    ts = localtime(&now);

    strftime(date, DATE_SIZE, "%d/%m/%y %a", ts);
}

List* initList(char* path, char const* file)
{
    if (file)
    {
        char filePath[PATH_SIZE];
        char* lastElementCh;

        lastElementCh = (char*) memccpy(filePath, path, '\0', PATH_SIZE) - 1;
        memccpy(lastElementCh, file, '\0', PATH_SIZE);

        return readList(filePath);
    }

    return malloc(sizeof(List));
}

List* readList(char const* path)
{
    FILE* pf;
    List* list = malloc(sizeof(List));
    pf = fopen(path, "rb");

    if (!pf)
    {    
        printf("File data not found\n");
        exit(1);
    }

    if (!fscanf(pf, "size: %u\n", &(list->size)))
    {
        printf("File data invalid\n");
        exit(1);
    }

    fscanf(pf, "totalValue: %f\n", &(list->totalValue));
    fscanf(pf, "earned: %f\n", &(list->earned));
    fscanf(pf, "lastModified: \"%[^\"]\"\n", list->lastModified);
    fscanf(pf, "\n");

    Paper** paper = &list->start;
    for (unsigned int i = 0; i < list->size; i++)
    {
        *paper = malloc(sizeof(Paper));
        fscanf(pf, "paper: %s\n", (*paper)->code);
        fscanf(pf, " averageValue: %f\n", &(*paper)->averageValue);
        fscanf(pf, " earned: %f\n", &(*paper)->earned);
        fscanf(pf, " quantity: %u\n", &(*paper)->quantity);
        fscanf(pf, " actualQuantity: %u\n", &(*paper)->actualQuantity);
        fscanf(pf, " dayOfBuy: \"%[^\"]\"\n", (*paper)->dayOfBuy);

        if ((*paper)->quantity != (*paper)->actualQuantity)
        {
            fscanf(pf, " dayOfSell: \"%[^\"]\"\n", (*paper)->dayOfSell);
        }
        paper = &(*paper)->next;
    }

    fclose(pf);
    return list;
}

void saveList(List* list, char const* path)
{
    FILE* pf;
    pf = fopen(path, "wb+");
    
    if (!pf)
    {
        printf("\ninvalid directory\n");
        exit(1);
    }

    fprintf(pf, "size: %u\n", list->size);
    fprintf(pf, "totalValue: %f\n", list->totalValue);
    fprintf(pf, "earned: %f\n", list->earned);
    fprintf(pf, "lastModified: \"%s\"\n", list->lastModified);
    fprintf(pf, "\n");

    Paper** paper = &list->start;
    for (unsigned int i = 0; i < list->size; ++i)
    {
        fprintf(pf, "paper: %s\n", (*paper)->code);
        fprintf(pf, " averageValue: %f\n", (*paper)->averageValue);
        fprintf(pf, " earned: %f\n", (*paper)->earned);    
        fprintf(pf, " quantity: %u\n", (*paper)->quantity);
        fprintf(pf, " actualQuantity: %u\n", (*paper)->actualQuantity);
        fprintf(pf, " dayOfBuy: \"%s\"\n", (*paper)->dayOfBuy);

        if ((*paper)->quantity != (*paper)->actualQuantity)
        {
            fprintf(pf, " dayOfSell: \"%s\"\n", (*paper)->dayOfSell);
        }
        paper = &(*paper)->next;
    }

    fclose(pf);
}
