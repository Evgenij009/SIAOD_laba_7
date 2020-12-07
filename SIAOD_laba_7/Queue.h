#include "stdlib.h"
#include <stdio.h>

typedef struct node_t
{
	int data;
	struct node_t *next;
} Node;

typedef struct queue_t
{
	Node* first;
	Node* last;
} Queue;

Queue* Queue_push(Queue* queue, int value)
{
	Node* node = (Node*)calloc(1, sizeof(Node));
	node->data = value;
	node->next = NULL;

	if (queue->first && queue->last)
	{
		queue->last->next = node;
		queue->last = node;
	}
	else
	{
		queue->first = queue->last = node;
	}

	return queue;
}

int Queue_empty(Queue* queue)
{
	if (queue->first && queue->last)
		return 0;
	else
		return 1;
}

int Queue_pop(Queue* queue)
{
	int value = 0;
	Node* node;
	if (queue->first)
	{
		node = queue->first;
		value = node->data;
		queue->first = queue->first->next;
		free(node);
	}

	return value;
}

void Queue_print(const Queue* queue)
{
	const Node* node = queue->first;

	// Перебираем все элементы и выводим их на дисплей
	for (; node; node = node->next)
	{
		printf("%d ", node->data);
	}
	printf("\n");
}