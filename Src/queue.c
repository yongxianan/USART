/*
 * queue.c
 *
 *  Created on: Dec 1, 2019
 *      Author: User
 */



#include "queue.h"

void queueInit(Queue *queue, size_t dataSize)
{
   queue->queueSize = 0;
   queue->dataSize = dataSize;
   queue->head = queue->tail = NULL;
   queue->TxItEnable=false;
}

bool enqueue(Queue *queue, void *data)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
    if(newNode == NULL){
        return false;
    }
    newNode->data = malloc(queue->dataSize);
    if(newNode->data == NULL){
        free(newNode);
        return false;
    }
    newNode->next = NULL;
    memcpy(newNode->data, data, queue->dataSize);
    if(queue->queueSize == 0){
        queue->head = queue->tail = newNode;
    }else{
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
	queue->queueSize++;
    return true;
}

bool dequeue(Queue *queue, void *data)
{
    if(queue->queueSize > 0){
        Node *temp = queue->head;
        memcpy(data, temp->data, queue->dataSize);
        if(queue->queueSize > 1){
            queue->head = queue->head->next;
        }
        else{
            queue->head = NULL;
            queue->tail = NULL;
        }
        queue->queueSize--;
        free(temp->data);
        free(temp);
		return true;
    }else{
		return false;
	}
}

int getQueueSize(Queue *queue){
    return queue->queueSize;
}



