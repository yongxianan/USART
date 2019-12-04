/*
 * uart.c
 *
 *  Created on: Oct 23, 2019
 *      Author: user1
 */

#include "uart.h"
#include <stdint.h>
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
void usartSend9Bit(USART *usart,uint16_t data){
	while((usart->SR & TRANSMIT_DR_EMPTY)!=TRANSMIT_DR_EMPTY);
	usart->DR |= (data & 0x1ff);
}
