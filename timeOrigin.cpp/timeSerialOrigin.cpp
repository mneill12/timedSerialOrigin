
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int sizeOfArray = 2;
const int up = 1;
const int down = 0;
const int randMax = 100;
int amountOfMerges = 0;
int recursiveExecution = 0;

void populateArray(int *elements);
void merge(int firstElement, int size, int direction, int *elements);
void bitonicSplit(int firstElement, int size, int direction, int *elements);
void sort(int *elements);
void printArray(int *elements);
bool isSorted(int *sorted);
int getElementCount();
bool isPowerOfTwo(int elementCount);
clock_t start, finish;
double timeSpent = 0;


int main() {

		sizeOfArray = getElementCount();

		printf("\nSize of Array is: %d\n", sizeOfArray);

		//Creater pointer array using malloc and populate it.
		int *elements;
		elements = (int*)malloc(sizeOfArray*sizeof(int));
		printf("\nPopulating array\n");

		for (int i = 0; i < sizeOfArray; ++i){
			elements[i] = rand() % randMax;
		}

		//Sort them
		start = clock();
		sort(elements);
		finish = clock();


		if (isSorted(elements)){
			printf("\nSorted \n");
		}

		else{
			printf("\nNot sorted \n");
		}

		printf("Final sequence ");
		printArray(elements);

		timeSpent = (double)(finish - start);

		printf("\nClocks per second %f: ", timeSpent);
		free(elements);

		printf("\n");
		system("pause");


	return 0;
}

void printArray(int *elements){

	for (int i = 0; i < sizeOfArray; i++){
		printf("%d ,", elements[i]);
	}
	printf("\n");
}

bool isSorted(int *elements){

	bool sorted = true;
	for (int i = 0; i < (sizeOfArray - 1); ++i){
		if (elements[i] > elements[i + 1]){
			sorted = false;
		}
	}
	return sorted;
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

		if (size == sizeOfArray)
		{
			printf("\nSequence before last merge\n");
			printArray(elements);
		}

		merge(firstElement, size, direction, elements);
	}
}

int getElementCount(){

	int inputCount;

	bool powerOfTwo = false;
	while (!powerOfTwo){

		printf("Enter amount of elements to be sorted: ");
		scanf_s("%d", &inputCount);
		printf("You entered: %d\n", inputCount);

		if (isPowerOfTwo(inputCount))
		{
			powerOfTwo = true;
		}
		else
		{
			printf("/nNot a power of 2, please re enter/n");
		}
	}

	return inputCount;
}

bool isPowerOfTwo(int elementCount){

	double logBase2 = log2(double(elementCount));

	if (round(logBase2) == logBase2)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void sort(int  *elements) {
	bitonicSplit(0, sizeOfArray, up, elements);
}