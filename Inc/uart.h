/*
 * uart.h
 *
 *  Created on: Oct 23, 2019
 *      Author: user1
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>


typedef struct USART USART;
struct USART{
	volatile	uint32_t	SR;		//0x00
	volatile	uint32_t	DR;		//0x04
	volatile	uint32_t	BRR;	//0x08
	volatile	uint32_t	CR1;	//0x0C
	volatile	uint32_t	CR2;	//0x10
	volatile	uint32_t	CR3;	//0x14
	volatile	uint32_t	GTPR;	//0x18
};

typedef struct UsartConfigData UsartConfigData;
struct UsartConfigData{
	int baudrate;
	int peripheralFreq;
	int muteModeAdress;
};

#define USART1 ((USART *)(0x40011000))
#define USART2 ((USART *)(0x40004400))
#define USART3 ((USART *)(0x40004800))
#define USART6 ((USART *)(0x40011400))

/*
 * USART_SR
 */
#define TRANSMIT_DR_EMPTY				(1<<7)
#define	TRANSMIT_COMPLETE				(1<<6)


/*
 * USART_CR1
 */
#define	OVERSAMPLING_16					(0<<15)
#define	OVERSAMPLING_8					(1<<15)

#define	USART_PRESCALER_OUTPUT_DISABLE	(0<<13)
#define	USART_ENABLE					(1<<13)

#define	WORD_8_BIT_DATA					(0<<12)
#define	WORD_9_BIT_DATA					(1<<12)

#define	WAKE_IDLE_LINE					(0<<11)
#define	WAKE_ADDRESS_MARK				(1<<11)

#define	PARITY_DISABLE					(0<<10)
#define	PARITY_ENABLE					(1<<10)

#define	PARITY_EVEN						(0<<9)
#define	PARITY_ODD						(1<<9)

#define	PARITY_ERROR_NO_IT				(0<<8)
#define	PARITY_ERROR_IT					(1<<8)

#define	TRANSMIT_EMPTY_NO_IT			(0<<7)
#define	TRANSMIT_EMPTY_IT				(1<<7)

#define	TRANSMIT_COMPLETE_NO_IT			(0<<6)
#define	TRANSMIT_COMPLETE_IT			(1<<6)

#define	RXNE_NO_IT						(0<<5)
#define	RXNE_IT							(1<<5)

#define	IDLE_NO_IT						(0<<4)
#define	IDLE_IT							(1<<4)

#define	TRANSMIT_DISABLE				(0<<3)
#define	TRANSMIT_ENABLE					(1<<3)

#define	RECEIVER_DISABLE				(0<<2)
#define	RECEIVER_ENABLE					(1<<2)

#define	RWU_RECEIVER_ACTIVE_MODE		(0<<1)
#define	RWU_RECEIVER_MUTE_MODE			(1<<1)

#define	NO_BREAK_CHAR_TRANSMIT			(0<<0)
#define	BREAK_CHAR_TRANSMIT				(1<<0)


/*
 * USART_CR2
 * shift 16 bit more relative to manual
 */
#define	LIN_MODE_DISABLE				(0<<30)
#define	LIN_MODE_ENABLE					(1<<30)

#define	USART_1_STOP_BIT				(0<<29)
#define	USART_0_5_STOP_BIT				(1<<29)
#define	USART_2_STOP_BIT				(2<<29)
#define	USART_1_5_STOP_BIT				(3<<29)

#define	CK_PIN_DISABLE					(0<<27)
#define	CK_PIN_ENABLE					(1<<27)

#define	CPOL_CK_STEADY_LOW				(0<<26)
#define	CPOL_CK_STEADY_HIGH				(1<<26)

#define	CPHA_FIRST_EDGE					(0<<25)
#define	CPHA_SECOND_EDGE				(1<<25)


void usartConfig(USART *usart,uint64_t CR,UsartConfigData *usartConfigData);
void usartSend9Bit(USART *usart,uint16_t data);
#endif /* UART_H_ */
