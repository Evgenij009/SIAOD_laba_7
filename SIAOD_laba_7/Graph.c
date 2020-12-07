#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Graph.h"
#include "Queue.h"

BOOL pathExist;

void printAllPathsUtil(int** matrix, int v1, int v2, int* visited, int size, int* path, int index)
{
	visited[v1] = TRUE;
	path[index] = v1;
	index++;

	if (v1 == v2)
	{
		int i;
		if (!pathExist)
			printf("\nFollowing are the paths  between %d and %d\n", path[0]+1, path[index - 1]+1);
		pathExist = TRUE;
		for (i = 0; i < index - 1; ++i)
			printf("%d->", path[i]+1);
		printf("%d\n", path[i]+1);
	}
	else
	{
		for (int i = 0; i < size; ++i)
		{
			if (matrix[v1][i] > 0 && !visited[i])
				printAllPathsUtil(matrix, i, v2, visited, size, path, index);
		}
	}

	index--;
	visited[v1] = FALSE;

}

void Graph_findAllPaths_betweenTwoVertices(int** array, int size, int source, int destination)
{
	--source;
	--destination;
	BOOL* visited = (BOOL*)calloc(size, sizeof(BOOL));
	for (int i = 0; i < size; ++i)
		visited[i] = FALSE;

	int* path = (int*)calloc(size, sizeof(int));
	int index = 0;

	pathExist = FALSE;

	printAllPathsUtil(array, source, destination, visited, size, path, index);
}

int** Graph_findPaths_Floida(int** matrix, int size, short flag)
{
	int** array = (int**)calloc(size, sizeof(int));
	for (int i = 0; i < size; ++i)
		*(array + i) = (int*)calloc(size, sizeof(int));

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (matrix[i][j] <= 0)
				array[i][j] = INFINITE * flag;
			else
				array[i][j] = matrix[i][j];
		
	for (int k = 0; k < size; ++k)
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				switch (flag)
				{
				case 1:
					if ((array[i][k] + array[k][j] < array[i][j]))
						array[i][j] = array[i][k] + array[k][j];
					break;
				case -1:
					if ((array[i][k] + array[k][j] > array[i][j]))
						array[i][j] = array[i][k] + array[k][j];
					break;
				}
				
	return array;
}

int Graph_findCentre(int** array, int size)
{
	int answer = 0, buff = 0;
	int *arrMaxLength = (int*)calloc(size, sizeof(int));

	for (int i = 0; i < size; ++i)
	{
		BOOL check = 0;
		for (int j = 0; j < size; ++j)
			if (array[j][i] > buff && array[j][i] != INFINITE)
			{
				buff = array[j][i];
				check = 1;
			}
		if (check == 1)
			arrMaxLength[i] = buff;
		else
			arrMaxLength[i] = INFINITE;
	}

	answer = arrMaxLength[0];
	for (int i = 1; i < size; ++i)
		if (arrMaxLength[i] < answer)
			answer = arrMaxLength[i];
	
	return answer;
}

BOOL bfs(int** matrix, int size, int source, int sink, int *parent)
{
	BOOL* visited = (BOOL*)calloc(size, sizeof(BOOL));
	
	Queue queue = { NULL, NULL };
	Queue_push(&queue, source);
	visited[source] = TRUE;
	parent[source] = -1;
	while (Queue_empty(&queue) == FALSE)
	{
		int u = Queue_pop(&queue);
		for (int i = 0; i < size; ++i)
		{
			int v = i;
			int capacity = matrix[u][v];
			if (visited[v] == FALSE && capacity > 0)
			{
				Queue_push(&queue, v);
				parent[v] = u;
				visited[v] = TRUE;
			}
		}
	}
	if (visited[sink] == TRUE)
		return TRUE;

	return FALSE;
}

int Graph_findMaxFlow(int **matrix, int size, int source, int destination)
{
	int maxflow = 0;

	int** rGraph = NULL;
	if ((rGraph = (int**)calloc(size, sizeof(int))) == NULL)
		return NULL;

	for (int i = 0; i < size; i++)
		if ((*(rGraph + i) = (int*)calloc(size, sizeof(int))) == NULL)
			return NULL;

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			rGraph[i][j] = matrix[i][j];

	int* parent = (int*)calloc(size, sizeof(int));

	int u, v;

	while (bfs(rGraph, size, source, destination, parent) == TRUE)
	{
		int path_flow = INT_MAX;
		int v = destination;
		while (v != source)
		{
			int u = parent[v];
			int capacity = rGraph[u][v];
			path_flow = min(path_flow, capacity);
			v = u;
		}
		v = destination;
		while (v != source)
		{
			int u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
			v = u;
		}
		maxflow += path_flow;
	}

	return maxflow;
}