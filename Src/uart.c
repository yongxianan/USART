/*
 * uart.c
 *
 *  Created on: Oct 23, 2019
 *      Author: user1
 */

#include "uart.h"
/*
 * RWU bit (mute mode) and WAKE bit
 * Address mark detection can be configure in CR1
 * register.
 */
void usartConfig(USART *usart,uint64_t CR,UsartConfigData *usartConfigData){
	int mantissa, fractional;
	float divider = 16.5;

	usart->CR1 = (uint32_t)(CR & 0xffff);
	usart->CR2 = (uint32_t)(((CR >>16 )& 0xffff) | 			\
				(usartConfigData->muteModeAdress & 0xF));
	usart->CR3 = (uint32_t)((CR >> 32)& 0xffff);

	divider = ((float)usartConfigData->peripheralFreq / (16 * usartConfigData->baudrate));
	mantissa = (int)divider;
	fractional = (int)((float)(divider-mantissa)*16);
	usart->BRR = (mantissa<<4)|(fractional);
}
void usartCR1(USART *usart,uint64_t CR){
	usart->CR1 |= (uint32_t)(CR & 0xffff);
}
void usartCR1Reset(USART *usart,uint64_t CR){
	usart->CR1 &= ~((uint32_t)(CR & 0xffff));
}
void usartSend9Bit(USART *usart,uint16_t data){
	while(!(usart->SR & TRANSMIT_COMPLETE));
	usart->DR = (data & 0x1ff);
}
/*
void usartSend9BitV2(USART *usart,Queue *queue, uint16_t data)
{
	enqueue(queue,(void *)&data);
	if(queue->TxItEnable==false){
		queue->TxItEnable=true;
		usartCR1(usart,TRANSMIT_COMPLETE_IT);
	}
}

void usartSendString(USART *usart,Queue *usartTXQ,char *str){
	int i=0;
	while(str[i]!='\n'){
		usartSend9BitV2(usart,usartTXQ,str[i]);
		i++;
	}
	usartSend9BitV2(usart,usartTXQ,'\n');
	usartSend9BitV2(usart,usartTXQ,'\r');
}

void ITDequeue(USART *usart,Queue *queue){
	uint16_t data=0;
	if(dequeue(queue,(void *)&data)){
		usart->DR = (data & 0x1ff);
	}else{
		usartCR1Reset(usart,TRANSMIT_COMPLETE_IT);
		queue->TxItEnable=false;
	}
}
*/
