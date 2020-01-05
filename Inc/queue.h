/*
 * queue.h
 *
 *  Created on: Dec 1, 2019
 *      Author: User
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct Node Node;
struct Node{
	void *data;
	Node *next;
};

typedef struct Queue Queue;
struct Queue{
    int queueSize;
    size_t dataSize;
    Node *head;
    Node *tail;
    bool TxItEnable;
};

void queueInit(Queue *queue, size_t memSize);
bool enqueue(Queue *queue, void *data);
bool dequeue(Queue *queue, void *data);

#endif /* QUEUE_H_ */
