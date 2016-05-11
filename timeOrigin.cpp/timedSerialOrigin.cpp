#include "timedSerialOriginHeader.h";
#include "userInputHeader.h";
#include "writeToCSVFileHeader.h";

//constants 
const int up = 1;
const int down = 0;
const int randMax = 100;
int amountOfMerges = 0;
int recursiveExecution = 0;

int executionCount;
int elementCount;

void createUnsortedArray(int* elements){

	for (int i = 0; i < elementCount; ++i){
		elements[i] = rand() % randMax - rand() % 5;
	}

}

bool isSorted(int *elements){

	bool sorted = true;
	for (int i = 0; i < (elementCount - 1); ++i){
		if (elements[i] > elements[i + 1]){
			sorted = false;
		}
	}
	return sorted;
}


double getElapsedTime(clock_t start, clock_t stop)
{
	double elapsed = ((double)(stop - start)) / CLOCKS_PER_SEC;
	printf("Elapsed time: %.3f\n", elapsed);

	return elapsed;
}

void compare(int i, int j, int direction, int *elements) {

	//Swap if the elements in the sorting network are contradictory to the direction of that swap
	if (direction == elements[i] > elements[j]){
		int temp = elements[i];
		elements[i] = elements[j];
		elements[j] = temp;
	}
}

void merge(int firstElement, int size, int direction, int *elements) {
	if (size>1) {

		int k = size / 2;
		amountOfMerges++;

		for (int i = firstElement; i < firstElement + k; i++){

			compare(i, i + k, direction, elements);
		}
		merge(firstElement, k, direction, elements);
		merge(firstElement + k, k, direction, elements);
	}
}


//Recursivly create bitonic sequence.  
void bitonicSplit(int firstElement, int size, int direction, int *elements) {
	if (size>1) {
		int k = size / 2;

		recursiveExecution++;

		bitonicSplit(firstElement, k, up, elements);
		bitonicSplit(firstElement + k, k, down, elements);
		merge(firstElement, size, direction, elements);
	}
}


void sort(int  *elements) {
	bitonicSplit(0, elementCount, up, elements);
}

int main(void)
{

	executionCount = getMaxProcessCount();
	int fixedExecutionCount = executionCount;

	bool runSort = true;

	//Pointers to store our results that we're writing to CSV files, allocate space entered buy the user

	double* timeResults = (double*)malloc(executionCount*sizeof(double));;
	char* arrayStates = (char*)malloc(executionCount*sizeof(char));
	int* elementsSizes = (int*)malloc(executionCount*sizeof(int));

	double time;
	clock_t start, stop;
	//Counter so we can assine values to the array in the execution loop
	int size = 2;
	while (runSort && executionCount != 0){

		runSort = true;

		//Get total element count
		elementCount = size;//getElementCount();
			
		//Malloc array, add values to it and write unsorted array to csv file
		int* values = (int*)malloc(elementCount*sizeof(int));
		createUnsortedArray(values);

		writeTimedSerialOriginArrayCsvFile(values, "preSorted", elementCount);

		//Do Sort and time it
		start = clock();
		sort(values);
		stop = clock();

		time = getElapsedTime(start, stop);

		char* arrayState;
		char arrayStateChar;

		if (isSorted(values)){

			printf("Is Sorted \n");
			arrayState = "sorted";
			arrayStateChar = 's';
		}
		else{

			printf("Not Sorted \n");
			arrayState = "unsorted";
			arrayStateChar = 'u';
		}

		writeTimedSerialOriginArrayCsvFile(values, arrayState, elementCount);

		//Allocate results values to pointers 
		*elementsSizes = size;
		*timeResults = time;
		*arrayStates = arrayStateChar;

		//Increment Result pointers
		timeResults++;
		arrayStates++;
		elementsSizes++;

		free(values);

		//Check again for user input
		size = size * 2;

		executionCount--;
	}

	printf("Execution ended. Writing results to C:\BitonicSortArrayCSVFiles /n");

	writeSortResultsToCsv(timeResults, "SerialBitonicSort", arrayStates, fixedExecutionCount, elementsSizes);

	getchar();
}