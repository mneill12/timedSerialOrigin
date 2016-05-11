#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define _CRT_SECURE_NO_DEPRECATE

//Function Prototypes 
void writeSortResultsToCsv(double* timeResults, char* sortType, char* arrayStates, int executionCount, int* elementsSizes);
void writeArrayAsCsvFile(char* filename, char* arrayState, int* array, int arrayLength);
void writeTimedSerialOriginArrayCsvFile(int* values, char* arrayState, int elementCount);
void writeSuggestedBlockThreadConfigToCsv(int* suggestedThreads, int* suggestedBlocks, int combinationsCount);


void incrementFileId(char* fileDirAndName);
int fileExists(const char *fileName);