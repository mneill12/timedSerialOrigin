#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


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