/*
 * state_machine.h
 *
 *  Created on: Nov 5, 2019
 *      Author: User
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_
#include <stdint.h>
#include <malloc.h>
#include "uart.h"
#include "gpio.h"
#include "queue.h"
#include "adc.h"




extern Queue execQueue,U1ISRQueue,U2ISRQueue,U3ISRQueue			\
,U4ISRQueue,U6ISRQueue,ADCISRQueue;



//typedef void(*SMFuncPtr)(Event *execEvent);
/*
typedef struct Event Event;
struct Event{
	EventName Name;
	DataType dataType;
	FuncPtrEnum funcPtrEnum;
	uint16_t length;
	uint16_t data[50];
	Event *next;
};
*/
void master1SM(Event *execEvent);
void slave2SM(Event *execEvent);
void slave3SM(Event *execEvent);
void slave4SM(Event *execEvent);
void slave6SM(Event *execEvent);
Event *createEvent(EventName eventName,SMFuncPtr smFuncPtr,uint16_t length,uint16_t *data,DataType dataType);

/*
typedef struct Event Event;
struct Event{
	EventName eventName;
	SMInfo *smInfo;
	uint32_t length;
	uint32_t data;
	Node *next;
	Event *nextEvent;
};

typedef void(*SMFuncPtr)(Event *event);

typedef struct SMInfo SMInfo;
struct SMInfo{
	SMFuncPtr smFuncPtr;
	State state;
	//data store by StateMachine

};
*/










/*
typedef enum{
	//used by master
	READ_BUTTON,
	CONTROL_LED,
	PROBE,
	SCAN_ADC_5,
	SCAN_ADC_13,
	//used by slave
	CHECK_ADDR,
	U2_MATCH_ADDRESS,
	U3_MATCH_ADDRESS,
	U6_MATCH_ADDRESS,
	SENDBACK_BUTTON,
	SET_LED,
	PROBE_LED,
	PROBE_BUTTON,
	//ADC state
	ADC5,
	ADC13
}State;



typedef struct{
	bool ReadFlag;
	uint16_t message;
	uint8_t buttonState;
	uint8_t ledState;
	State state;
	uint32_t adcData;
}Info;

typedef struct{
	Info *info;
	Queue *usartQueue;
}SMInfo;

//void stateMachine(USART *usart, SMInfo *smInfo);
void checkAddressV2(Info *UInfo,uint16_t expAddress,State setMatchAddr);
void stateMachineV2(Info *UInfo,Queue *usartTXQ);
*/
#endif /* STATE_MACHINE_H_ */
