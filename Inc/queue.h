/*
 * queue.h
 *
 *  Created on: Dec 1, 2019
 *      Author: User
 */

#ifndef QUEUE_H_
#define QUEUE_H_
//#include "cmsis_gcc.h"
#include "nvic.h"
#include <string.h>
extern int interrupts[];
/*
typedef struct Node Node;
struct Node{
	void *data;
	Node *next;
};
*/
typedef enum{
	START_EVENT,
	START_EVENT_SL2,

	//master1 event
	GET_ADC5,
	GET_ADC13,
	BUTTON_COMMAND,
	READ_BUTTON,
	CONTROL_LED,
	PROBE,

	//slave2
	DETECT_COMMAND,
	SEND_BUTTON_STATE,

	//slave6
	RX_PROBE,

	AVERAGE_DATA,
	SEND_PC
}EventName;

typedef enum{
	TX_DATA,
	RX_DATA
}DataType;
/*
typedef enum{
	MASTER1SM,
	SLAVE2SM,
	SLAVE3SM,
	SLAVE4SM,
	SLAVE6SM
}FuncPtrEnum;
*/

typedef struct Event Event;

typedef void(*SMFuncPtr)(Event *execEvent);

struct Event{
	EventName Name;
	DataType dataType;
	SMFuncPtr smFuncPtr;
	uint16_t length;
	uint16_t data[50];
	Event *next;
};

typedef struct Queue Queue;
struct Queue{
    int queueSize;
    Event *head;
    Event *tail;
};


/*
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
*/
#endif /* QUEUE_H_ */
