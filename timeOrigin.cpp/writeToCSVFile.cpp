#include "writeToCSVFileHeader.h"

void writeSortResultsToCsv(double* timeResults, char* sortType, char* arrayStates, int executionCount, int* elementsSizes){

	struct tm *tm;
	time_t t;
	char str_time[100];
	char str_date[100];

	t = time(NULL);
	#pragma warning (disable : 4996)
	tm = localtime(&t);
	strftime(str_time, sizeof(str_time), "-Time-%H-%M-%S", tm);
	strftime(str_date, sizeof(str_date), "-Date-%d-%m-%Y", tm);

	char* filename = "TimedResults";

	char fileDirAndName[120] = "C:/BitonicSortArrayCSVFiles/";
	//Use array state as folder name
	strcat_s(fileDirAndName, "timedResults");
	strcat_s(fileDirAndName, "/");
	strcat_s(fileDirAndName, filename);
	strcat_s(fileDirAndName, str_date);
	strcat_s(fileDirAndName, str_time);
	strcat_s(fileDirAndName, ".csv");

	#pragma warning (disable : 4996)
	FILE* file = fopen(fileDirAndName, "w");

	//Column headers 
	fprintf(file, "Time, Elements, result");

	for (int i = 0; i < executionCount; i++){

		sortType--;
		timeResults--;
		arrayStates--;
		elementsSizes--;

		fprintf(file, "\n");

		fprintf(file, "%d", *elementsSizes);
		fprintf(file, ",%.3f", *timeResults);
		

		if (*arrayStates == 's'){
			fprintf(file, ",sorted");
		}
		else if (*arrayStates == 'u'){
			fprintf(file, ",unsorted");
		}
	}

	//Add Array State at the end
	fprintf(file, "\n");

	fclose(file);
}

void writeSuggestedBlockThreadConfigToCsv(int* suggestedThreads, int* suggestedBlocks, int combinationsCount){

	struct tm *tm;
	time_t t;
	char str_time[100];
	char str_date[100];

	t = time(NULL);
	tm = localtime(&t);

	strftime(str_time, sizeof(str_time), "-Time-%H-%M-%S", tm);
	strftime(str_date, sizeof(str_date), "-Date-%d-%m-%Y", tm);

	char* filename = "suggestedBlockThreadConfig";

	char fileDirAndName[120] = "C:/BitonicSortArrayCSVFiles/";
	//Use array state as folder name
	strcat_s(fileDirAndName, "blockThreadConfigs");
	strcat_s(fileDirAndName, "/");
	strcat_s(fileDirAndName, filename);
	strcat_s(fileDirAndName, str_date);
	strcat_s(fileDirAndName, str_time);
	strcat_s(fileDirAndName, ".csv");

	FILE* file = fopen(fileDirAndName, "w");

	//Column headers 
	fprintf(file, "BlocksCount, ThreadCount");

	for (int i = 1; i <= combinationsCount; i++){

		fprintf(file, "\n");

		fprintf(file, "%d ", *suggestedBlocks);
		fprintf(file, ",%d ", *suggestedThreads);

		fprintf(file, ",\n");

		suggestedBlocks++;
		suggestedThreads++;
	}

	fclose(file);
}

void writeArrayAsCsvFile(char* filename, char* arrayState, int* array, int arrayLength){

	struct tm *tm;
	time_t t;
	char str_time[100];
	char str_date[100];

	t = time(NULL);
	tm = localtime(&t);

	strftime(str_time, sizeof(str_time), "-Time-%H-%M-%S", tm);
	strftime(str_date, sizeof(str_date), "-Date-%d-%m-%Y", tm);

	char fileDirAndName[120] = "C:/BitonicSortArrayCSVFiles/";
	//Use array state as folder name, Create file name from string of array
	strcat_s(fileDirAndName, arrayState);
	strcat_s(fileDirAndName, "/");
	strcat_s(fileDirAndName, filename);
	strcat_s(fileDirAndName, str_date);
	strcat_s(fileDirAndName, str_time);

	strcat_s(fileDirAndName, ".csv");

	printf("");
	FILE* file = fopen(fileDirAndName, "w");

	for (int i = 0; i < arrayLength; i++){
		fprintf(file, "%d \n", *array);
		array++;
	}

	//Add Array State at the end
	fprintf(file, "\n ");
	fprintf(file, arrayState);

	fclose(file);
}
void writeTimedSerialOriginArrayCsvFile(int* values, char* arrayState, int elementCount){

	char* string = "SortElements%TimedOrigin";
	char filename[100];
	sprintf(filename, string, elementCount);

	writeArrayAsCsvFile(filename, arrayState, values, elementCount);

}

int fileExists(const char *fileName)
{
	FILE *file;
	if (file = fopen(fileName, "r"))
	{
		fclose(file);
		return 1;
	}
	return 0;
}

void incrementFileId(char* fileDirAndName){

	char fileIdx = fileDirAndName[strlen(fileDirAndName) - 1];

	int fileIdxInt = fileIdx - '0';
	fileIdxInt++;
	fileIdx = fileIdxInt + '0';
	fileDirAndName[strlen(fileDirAndName) - 1] = fileIdx;

}