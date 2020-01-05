/*
 * state_machine.h
 *
 *  Created on: Nov 5, 2019
 *      Author: User
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_
#include <stdbool.h>
#include "uart.h"
#include "gpio.h"
#include "queue.h"
#include "adc.h"

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
#endif /* STATE_MACHINE_H_ */
