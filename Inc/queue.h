/*
 * queue.h
 *
 *  Created on: Dec 1, 2019
 *      Author: User
 */

#ifndef QUEUE_H_
#define QUEUE_H_

// A structure to represent a queue
typedef struct
{
	int front, rear, size;
	unsigned capacity;
	int* array;
}Queue;

Queue* createQueue(unsigned capacity);
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, int item);
int dequeue(Queue* queue);

#endif /* QUEUE_H_ */
