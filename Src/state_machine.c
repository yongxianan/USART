/*
 * state_machine.c
 *
 *  Created on: Nov 5, 2019
 *      Author: User
 */

#include "state_machine.h"



Event *createEvent(EventName eventName,SMFuncPtr smFuncPtr,uint16_t length,uint16_t *data,DataType dataType){
	Event *newEvent=malloc(sizeof(Event));
	newEvent->Name=eventName;
	newEvent->length=length;
	newEvent->smFuncPtr=smFuncPtr;
	newEvent->dataType=dataType;
	for(int i=0;i<length;i++){
		newEvent->data[i] = data[i];
	}
	return newEvent;
}

void master1SM(Event *execEvent)
{
	static uint32_t adc5Data,adc13Data,buttonState,ledState;
	uint16_t data[7];
	static EventName state;
	Event *newEvent=NULL;

	if(execEvent->Name==START_EVENT){
		state=GET_ADC5;
	}

	switch(state){//USART1 master
	case GET_ADC5:
		//release PROBE

		newEvent=createEvent(GET_ADC5,&master1SM,1,data,RX_DATA);
		eventEnqueue(&ADCISRQueue,newEvent);
		adcConfig(ADC1, ADC_CR2_SWSTART);
		state=GET_ADC13;
		break;
	case GET_ADC13:
		//release GET_ADC5
		adc5Data=execEvent->data[0];

		newEvent=createEvent(GET_ADC13,&master1SM,1,data,RX_DATA);
		eventEnqueue(&ADCISRQueue,newEvent);
		adcConfig(ADC1, ADC_CR2_SWSTART);
		state=BUTTON_COMMAND;
		break;
	case BUTTON_COMMAND:
		//release GET_ADC13
		adc13Data=execEvent->data[0];

		data[0]=0b100100001;
		data[1]=0b000000001;
		newEvent=createEvent(BUTTON_COMMAND,&master1SM,2,data,TX_DATA);
		eventEnqueue(&U1ISRQueue,newEvent);

		data[0]=0b0;
		data[1]=0b0;
		newEvent=createEvent(READ_BUTTON,&master1SM,1,data,RX_DATA);
		eventEnqueue(&U1ISRQueue,newEvent);
		usartCR1(USART1,TRANSMIT_EMPTY_IT);

		state=READ_BUTTON;
		break;
	case READ_BUTTON:
		//release BUTTON_COMMAND
		state=CONTROL_LED;
		break;

	case CONTROL_LED:
		//release READ_BUTTON
		buttonState=execEvent->data[0];

		data[0]=0b100100010;
		data[1]=buttonState;//use buttonState control led
		newEvent=createEvent(BUTTON_COMMAND,&master1SM,2,data,TX_DATA);
		eventEnqueue(&U1ISRQueue,newEvent);
		usartCR1(USART1,TRANSMIT_EMPTY_IT);
		//state=PROBE;
		state=GET_ADC5;
		break;
		/*
	case PROBE:
		//release CONTROL_LED
		ledState=buttonState;

		data[0]=0b100100011;
		data[1]=adc5Data;
		data[2]=adc13Data;
		data[3]=buttonState;
		data[4]=ledState;
		newEvent=createEvent(PROBE,&master1SM,5,data,TX_DATA);
		state=GET_ADC5;
		eventEnqueue(&U1ISRQueue,newEvent);
		usartCR1(USART1,TRANSMIT_EMPTY_IT);
		break;
		*/
	}
	free(execEvent);
}

void slave2SM(Event *execEvent)
{
	uint16_t data[3];
	static EventName state;
	Event *newEvent=NULL;

	if(execEvent->Name==START_EVENT){
		state=DETECT_COMMAND;
	}

	switch(state){
	case DETECT_COMMAND:
		//release SEND_BUTTON_STATE

		newEvent=createEvent(DETECT_COMMAND,&slave2SM,2,data,RX_DATA);
		state=SEND_BUTTON_STATE;
		eventEnqueue(&U2ISRQueue, newEvent);
		break;
	case SEND_BUTTON_STATE:
		//release DETECT_COMMAND

		data[0]=(uint32_t)readGPIO(GPIOA,0);
		newEvent=createEvent(SEND_BUTTON_STATE,&slave2SM,1,data,TX_DATA);
		state=DETECT_COMMAND;
		eventEnqueue(&U2ISRQueue, newEvent);
		usartCR1(USART2,TRANSMIT_EMPTY_IT);
		break;
	}
	free(execEvent);
}

void slave3SM(Event *execEvent)
{
	uint16_t data[3];
	static EventName state;
	Event *newEvent=NULL;

	if(execEvent->Name==START_EVENT){
		state=DETECT_COMMAND;
	}
	switch(state){
	case DETECT_COMMAND:
		//release DETECT_COMMAND
		setResetGPIO(GPIOG,13, (execEvent->data[1] & 0x1));

		newEvent=createEvent(DETECT_COMMAND,&slave3SM,2,data,RX_DATA);
		state=DETECT_COMMAND;
		eventEnqueue(&U3ISRQueue, newEvent);
		break;
	}
	free(execEvent);
}

void slave4SM(Event *execEvent)
{
	static EventName state;
	Event *newEvent=NULL;
	uint16_t data[100];
	if(execEvent->Name==AVERAGE_DATA){
		state=AVERAGE_DATA;
	}
	switch(state){
	case AVERAGE_DATA:
		sprintf(data,	"ADC 5 = %d \n\r"
						"ADC 13 = %d \n\r", 				\
						execEvent->data[0],execEvent->data[1]);
		strDecideMsg(data,execEvent->data[2],"BUTTON ON\n\r","BUTTON OFF\n\r");
		strDecideMsg(data,execEvent->data[3],"LED ON\n\r","LED OFF\n\r");
		newEvent=createEvent(SEND_PC,&slave4SM,strlen(data),data,TX_DATA);
		eventEnqueue(&U4ISRQueue,newEvent);
		usartCR1(UART4,TRANSMIT_EMPTY_IT);
		state=SEND_PC;
		break;
	case SEND_PC:
		//release SEND_PC
		state=SEND_PC;
		break;
	}
	free(execEvent);
}

void slave6SM(Event *execEvent)
{
	static uint16_t buttonState,ledState,i=0;
	static uint32_t adc5Data,adc13Data;
	uint16_t data[8];
	static EventName state;
	Event *newEvent=NULL;

	if(execEvent->Name==START_EVENT){
		state=DETECT_COMMAND;
	}

	switch(state){
	case DETECT_COMMAND:
		//not taking any adc data in the beginning because START_EVENT
		//is enqueue by user in the beginning for usart6 to be ready
		//to receive from master
		newEvent=createEvent(RX_PROBE,&slave6SM,5,data,RX_DATA);
		state=RX_PROBE;
		eventEnqueue(&U3ISRQueue, newEvent);
		break;
	case RX_PROBE:
		//release DETECT_COMMAND or RX_PROBE
		newEvent=createEvent(RX_PROBE,&slave6SM,5,data,RX_DATA);
		eventEnqueue(&U3ISRQueue,newEvent);
		adc5Data+=execEvent->data[1];
		adc13Data+=execEvent->data[2];
		buttonState=execEvent->data[3];
		ledState=execEvent->data[4];
		i++;
		if(i==999){
			i=0;
			data[0]=(uint16_t)adc5Data/1000;
			data[1]=(uint16_t)adc5Data/1000;
			data[2]=buttonState;
			data[3]=ledState;
			newEvent=createEvent(AVERAGE_DATA,&slave4SM,4,data,TX_DATA);
			eventEnqueue(&execQueue,newEvent);//tx into slave4SM
		}
		state=RX_PROBE;
		break;
	}
	free(execEvent);
}



void strDecideMsg(char *str,bool statement,char *TrueMsg,char *FalseMsg)
{
	if(statement==0){
		strcat(str,FalseMsg);
	}else{
		strcat(str,TrueMsg);
	}
}

Event *isrUsartEvent(USART *usart,Queue *queue,Event *event,uint32_t *dataIndex){
	if(*dataIndex==0){
		event=eventDequeue(queue);
	}

	if(usart->SR & USART_READY_TO_READ){
		event->data[*dataIndex]=usart->DR;
	}else if(usart->SR & TRANSMIT_DR_EMPTY){
		usart->DR = (event->data[*dataIndex] & 0x1ff);
	}

	(*dataIndex)++;

	if(*dataIndex==event->length){
		usartCR1Reset(usart,TRANSMIT_EMPTY_IT);
		eventEnqueue(&execQueue,event);
		//release event
		(*dataIndex)=0;
	}
	return event;
}
/*
void checkAddressV2(Info *info,uint16_t expAddress,State setMatchAddr){
	if(info->message == expAddress){
		info->state = setMatchAddr;
	}else if(info->message & 0b100000000){
		info->state = CHECK_ADDR;
	}
}

void msgTrueFalse(USART *usart,Queue *usartTXQ,bool statement,char *TrueMsg,char *FalseMsg){
	if(statement==0){
		usartSendString(USART6,usartTXQ,FalseMsg);
	}else{
		usartSendString(USART6,usartTXQ,TrueMsg);
	}
}
void stateMachineV2(Info *info,Queue *usartTXQ){
	volatile uint16_t buttonState;
	static uint32_t adc5Data, adc13Data;
	char str[80];
	switch(info->state){
		//ADC interrupt
		case ADC5:
		adc5Data=info->adcData;
		info->state=ADC13;
		break;
		case ADC13:
		adc13Data=info->adcData;
		info->state=ADC5;
		break;

		//USART2 slave
		case U2_MATCH_ADDRESS:
		info->state=SENDBACK_BUTTON;
		break;
		case SENDBACK_BUTTON:
		buttonState=(uint16_t)readGPIO(GPIOA,0);
		//USART2 send to master USART1
		usartSend9BitV2(USART2,usartTXQ,0xff & buttonState);
		info->state=CHECK_ADDR;
		break;

		//USART3 slave
		case U3_MATCH_ADDRESS:
		info->state=SET_LED;
		break;
		case SET_LED:
		setResetGPIO(GPIOG,13, (info->message & 0x1));
		info->state=CHECK_ADDR;
		break;

		//USART6 slave
		case U6_MATCH_ADDRESS:
		info->state=PROBE_LED;
		break;
		case PROBE_LED:
		//send back to PC (terminal)
		msgTrueFalse(USART6,usartTXQ,info->message,"LED ON\n\r","LED OFF\n\r");
		info->state=PROBE_BUTTON;
		break;
		case PROBE_BUTTON:
		//send back to PC (terminal)
		msgTrueFalse(USART6,usartTXQ,info->message,"BUTTON ON\n\r","BUTTON OFF\n\r");

		sprintf(str, "ADC 5 = %d \n\r", adc5Data);
		usartSendString(USART6,usartTXQ,str);

		sprintf(str, "ADC 13 = %d \n\r", adc13Data);
		usartSendString(USART6,usartTXQ,str);

		info->state=CHECK_ADDR;
		break;

		//USART1 master
		case READ_BUTTON:
		usartSend9BitV2(USART1,usartTXQ,0b100100001);//USART2 address
		usartSend9BitV2(USART1,usartTXQ,0b000000001);//command
		info->state = CONTROL_LED;
		break;
		case CONTROL_LED:
		info->ReadFlag = true;
		usartSend9BitV2(USART1,usartTXQ,0b100100010);//USART3 address
		info->ledState=info->buttonState;//led depend on button state
		usartSend9BitV2(USART1,usartTXQ,(uint16_t) (0xff & info->ledState));
		info->state = SCAN_ADC_5;
		info->ReadFlag = false;
		break;
		//master request ADC
		case SCAN_ADC_5:
		adcConfig(ADC1, ADC_CR2_SWSTART);
		info->state = SCAN_ADC_13;
		break;
		case SCAN_ADC_13:
		adcConfig(ADC1, ADC_CR2_SWSTART);
		info->state = PROBE;
		break;
		//USART1 master
		case PROBE:
		info->ReadFlag = true;
		usartSend9BitV2(USART1,usartTXQ,0b100100011);//USART3 address
		usartSend9BitV2(USART1,usartTXQ,(uint16_t) (0xff & info->ledState));
		usartSend9BitV2(USART1,usartTXQ,(uint16_t) (0xff & info->buttonState));

		info->state = READ_BUTTON;
		info->ReadFlag = false;
		break;
	}
}
*/
