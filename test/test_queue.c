#include "unity.h"
#include "queue.h"
//#include <malloc.h>

void setUp(void)
{
}

void tearDown(void)
{
}

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
};
*/
void test_queueInit(void)
{
    Queue queue;
	queueInit(&queue, sizeof(uint16_t));
    TEST_ASSERT_EQUAL(0,queue.queueSize);
    TEST_ASSERT_EQUAL(sizeof(uint16_t),queue.dataSize);
    TEST_ASSERT_EQUAL(NULL,queue.head);
    TEST_ASSERT_EQUAL(NULL,queue.tail);
}

void test_enqueue_dequeue(void)
{
	Queue queue = { .queueSize=0, .dataSize=sizeof(uint16_t),	\
	.head=NULL, .tail=NULL};
	
	uint16_t data=16;
	
	TEST_ASSERT_EQUAL(true,enqueue(&queue, (void *)&data));
	
	TEST_ASSERT_EQUAL(16,(uint16_t) *(uint16_t * )((queue.head)->data));
	TEST_ASSERT_EQUAL(16,(uint16_t) *(uint16_t * )((queue.tail)->data));
	TEST_ASSERT_EQUAL(1,queue.queueSize);
	TEST_ASSERT_EQUAL(sizeof(uint16_t),queue.dataSize);
	
	data=33;
	
	TEST_ASSERT_EQUAL(true,enqueue(&queue, (void *)&data));
	
	TEST_ASSERT_EQUAL(16,(uint16_t) *(uint16_t * )((queue.head)->data));
	TEST_ASSERT_EQUAL(33,(uint16_t) *(uint16_t * )((queue.tail)->data));
	TEST_ASSERT_EQUAL(2,queue.queueSize);
	TEST_ASSERT_EQUAL(sizeof(uint16_t),queue.dataSize);
	
	data=55;
	
	TEST_ASSERT_EQUAL(true,enqueue(&queue, (void *)&data));
	
	TEST_ASSERT_EQUAL(16,(uint16_t) *(uint16_t * )((queue.head)->data));
	TEST_ASSERT_EQUAL(55,(uint16_t) *(uint16_t * )((queue.tail)->data));
	TEST_ASSERT_EQUAL(3,queue.queueSize);
	TEST_ASSERT_EQUAL(sizeof(uint16_t),queue.dataSize);
	
	//from here start testing dequeue
	uint16_t DQData=0;
	
	TEST_ASSERT_EQUAL(true,dequeue(&queue, (void *)&DQData));
	
	TEST_ASSERT_EQUAL(16,DQData);
	TEST_ASSERT_EQUAL(33,(uint16_t) *(uint16_t * )((queue.head)->data));
	TEST_ASSERT_EQUAL(55,(uint16_t) *(uint16_t * )((queue.tail)->data));
	TEST_ASSERT_EQUAL(2,queue.queueSize);
	TEST_ASSERT_EQUAL(sizeof(uint16_t),queue.dataSize);
	
	TEST_ASSERT_EQUAL(true,dequeue(&queue, (void *)&DQData));
	
	TEST_ASSERT_EQUAL(33,DQData);
	TEST_ASSERT_EQUAL(55,(uint16_t) *(uint16_t * )((queue.head)->data));
	TEST_ASSERT_EQUAL(55,(uint16_t) *(uint16_t * )((queue.tail)->data));
	TEST_ASSERT_EQUAL(1,queue.queueSize);
	TEST_ASSERT_EQUAL(sizeof(uint16_t),queue.dataSize);
	
	TEST_ASSERT_EQUAL(true,dequeue(&queue, (void *)&DQData));
	
	TEST_ASSERT_EQUAL(55,DQData);
	TEST_ASSERT_EQUAL(NULL,queue.head);
	TEST_ASSERT_EQUAL(NULL,queue.tail);
	TEST_ASSERT_EQUAL(0,queue.queueSize);
	TEST_ASSERT_EQUAL(sizeof(uint16_t),queue.dataSize);
	
	//return false when queue is empty
	TEST_ASSERT_EQUAL(false,dequeue(&queue, (void *)&DQData));
	
	TEST_ASSERT_EQUAL(55,DQData);
	TEST_ASSERT_EQUAL(NULL,queue.head);
	TEST_ASSERT_EQUAL(NULL,queue.tail);
	TEST_ASSERT_EQUAL(0,queue.queueSize);
	TEST_ASSERT_EQUAL(sizeof(uint16_t),queue.dataSize);
}
	