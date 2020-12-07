#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "ReaderFile.h"

#define ERROR_OPEN_FILE "Error! Cannot be opened. Please,\n \
                         check your file and to try again.\n"

int ReaderFile_getSizeMatrixFromFile(FILE* fPtr);
int** ReaderFile_allocateMemory(int size);
void ReaderFile_readFile(FILE* fPtr, int** array);

int** ReaderFile_getMatrix(char *pathFile, int *sizePtr)
{
	int** array = NULL;
	FILE* fPtr = fopen(pathFile, "r");
	if (fPtr == NULL)
	{
		printf(ERROR_OPEN_FILE);
		return NULL;
	}
	else
	{
		int size = ReaderFile_getSizeMatrixFromFile(fPtr);
		*sizePtr = size;
		array = ReaderFile_allocateMemory(size);
		ReaderFile_readFile(fPtr, array, size);
	}
	fclose(fPtr);

	return array;
}

void ReaderFile_readFile(FILE *fPtr, int **array, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			fscanf(fPtr, "%d", &array[i][j]); 
	//fread(array[i], sizeof(int), 1, fPtr);
}

int** ReaderFile_allocateMemory(int size)
{
	int** array = NULL;
	if ((array = (int**)calloc(size, sizeof(int))) == NULL)
		return NULL;

	for (int i = 0; i < size; i++)
		if ((*(array + i) = (int*)calloc(size, sizeof(int))) == NULL)
			return NULL;

	return array;
}

int ReaderFile_getSizeMatrixFromFile(FILE* fPtr)
{
	int size;
	fseek(fPtr, 0, SEEK_SET);
	fscanf(fPtr, "%d", &size);

	return size;
}