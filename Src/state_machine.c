/*
 * state_machine.c
 *
 *  Created on: Nov 5, 2019
 *      Author: User
 */

#include "state_machine.h"


void checkAddressV2(Info *UInfo,uint16_t expAddress,State setMatchAddr){
	if(UInfo->message == expAddress){
		UInfo->state = setMatchAddr;
	}else if(UInfo->message & 0b100000000){
		UInfo->state = CHECK_ADDR;
	}
}

void msgTrueFalse(USART *usart,Queue *usartTXQ,bool statement,char *TrueMsg,char *FalseMsg){
	if(statement==0){
		usartSendString(USART6,usartTXQ,FalseMsg);
	}else{
		usartSendString(USART6,usartTXQ,TrueMsg);
	}
}

void stateMachineV2(Info *UInfo,Queue *usartTXQ){
	volatile uint16_t buttonState;
	static uint32_t adc5Data, adc13Data;
	char str[80];
	switch(UInfo->state){
		//ADC interrupt
		case ADC5:
		adc5Data=UInfo->adcData;
		UInfo->state=ADC13;
		break;
		case ADC13:
		adc13Data=UInfo->adcData;
		UInfo->state=ADC5;
		break;

		//USART2 slave
		case U2_MATCH_ADDRESS:
		UInfo->state=SENDBACK_BUTTON;
		break;
		case SENDBACK_BUTTON:
		buttonState=(uint16_t)readGPIO(GPIOA,0);
		//USART2 send to master USART1
		usartSend9BitV2(USART2,usartTXQ,0xff & buttonState);
		UInfo->state=CHECK_ADDR;
		break;

		//USART3 slave
		case U3_MATCH_ADDRESS:
		UInfo->state=SET_LED;
		break;
		case SET_LED:
		setResetGPIO(GPIOG,13, (UInfo->message & 0x1));
		UInfo->state=CHECK_ADDR;
		break;

		//USART6 slave
		case U6_MATCH_ADDRESS:
		UInfo->state=PROBE_LED;
		break;
		case PROBE_LED:
		//send back to PC (terminal)
		msgTrueFalse(USART6,usartTXQ,UInfo->message,"LED ON\n\r","LED OFF\n\r");
		UInfo->state=PROBE_BUTTON;
		break;
		case PROBE_BUTTON:
		//send back to PC (terminal)
		msgTrueFalse(USART6,usartTXQ,UInfo->message,"BUTTON ON\n\r","BUTTON OFF\n\r");

		sprintf(str, "ADC 5 = %d \n\r", adc5Data);
		usartSendString(USART6,usartTXQ,str);

		sprintf(str, "ADC 13 = %d \n\r", adc13Data);
		usartSendString(USART6,usartTXQ,str);

		UInfo->state=CHECK_ADDR;
		break;

		//USART1 master
		case READ_BUTTON:
		usartSend9BitV2(USART1,usartTXQ,0b100100001);//USART2 address
		usartSend9BitV2(USART1,usartTXQ,0b000000001);//command
		UInfo->state = CONTROL_LED;
		break;
		case CONTROL_LED:
		UInfo->ReadFlag = true;
		usartSend9BitV2(USART1,usartTXQ,0b100100010);//USART3 address
		UInfo->ledState=UInfo->buttonState;//led depend on button state
		usartSend9BitV2(USART1,usartTXQ,(uint16_t) (0xff & UInfo->ledState));
		UInfo->state = SCAN_ADC_5;
		UInfo->ReadFlag = false;
		break;
		//master request ADC
		case SCAN_ADC_5:
		adcConfig(ADC1, ADC_CR2_SWSTART);
		UInfo->state = SCAN_ADC_13;
		break;
		case SCAN_ADC_13:
		adcConfig(ADC1, ADC_CR2_SWSTART);
		UInfo->state = PROBE;
		break;
		//USART1 master
		case PROBE:
		UInfo->ReadFlag = true;
		usartSend9BitV2(USART1,usartTXQ,0b100100011);//USART3 address
		usartSend9BitV2(USART1,usartTXQ,(uint16_t) (0xff & UInfo->ledState));
		usartSend9BitV2(USART1,usartTXQ,(uint16_t) (0xff & UInfo->buttonState));

		UInfo->state = READ_BUTTON;
		UInfo->ReadFlag = false;
		break;
	}
}
