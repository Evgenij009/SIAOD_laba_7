#include <stdio.h>
#include <locale.h>
#include "ReaderFile.h"
#include "Graph.h"

void printMatrix(int**, int);

int main()
{
	setlocale(LC_ALL, "Rus");
	int size, source = 1, destination = 5;
	const int** array = ReaderFile_getMatrix("test.dat", &size);
	printf("File read succes.\nSize: %d\n", size);
	printMatrix(array, size);

	Graph_findAllPaths_betweenTwoVertices(array, size, source, destination);

	int answer = Graph_findCentre(array, size);
	printf("\nCenter Graph: %d\n", answer);

	int** arrayAnswer = Graph_findPaths_Floida(array, size, 1);
	printf("\nMin paths: \n");
	printMatrix(arrayAnswer, size);

	arrayAnswer = Graph_findPaths_Floida(array, size, -1);
	printf("\nMax paths: \n");
	printMatrix(arrayAnswer, size);

	return 0;
}

void printMatrix(int** array, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%7d ", array[i][j]);
		printf("\n");
	}
}