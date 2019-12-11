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
#define	USART_READY_TO_READ				(1<<5)


/*
 * USART_CR1
 */
#define	OVERSAMPLING_16					(0ULL<<15)
#define	OVERSAMPLING_8					(1ULL<<15)

#define	USART_PRESCALER_OUTPUT_DISABLE	(0ULL<<13)
#define	USART_ENABLE					(1ULL<<13)

#define	WORD_8_BIT_DATA					(0ULL<<12)
#define	WORD_9_BIT_DATA					(1ULL<<12)

#define	WAKE_IDLE_LINE					(0ULL<<11)
#define	WAKE_ADDRESS_MARK				(1ULL<<11)

#define	PARITY_DISABLE					(0ULL<<10)
#define	PARITY_ENABLE					(1ULL<<10)

#define	PARITY_EVEN						(0ULL<<9)
#define	PARITY_ODD						(1ULL<<9)

#define	PARITY_ERROR_NO_IT				(0ULL<<8)
#define	PARITY_ERROR_IT					(1ULL<<8)

#define	TRANSMIT_EMPTY_NO_IT			(0ULL<<7)
#define	TRANSMIT_EMPTY_IT				(1ULL<<7)

#define	TRANSMIT_COMPLETE_NO_IT			(0ULL<<6)
#define	TRANSMIT_COMPLETE_IT			(1ULL<<6)

#define	RXNE_NO_IT						(0ULL<<5)
#define	RXNE_IT							(1ULL<<5)

#define	IDLE_NO_IT						(0ULL<<4)
#define	IDLE_IT							(1ULL<<4)

#define	TRANSMIT_DISABLE				(0ULL<<3)
#define	TRANSMIT_ENABLE					(1ULL<<3)

#define	RECEIVER_DISABLE				(0ULL<<2)
#define	RECEIVER_ENABLE					(1ULL<<2)

#define	RWU_RECEIVER_ACTIVE_MODE		(0ULL<<1)
#define	RWU_RECEIVER_MUTE_MODE			(1ULL<<1)

#define	NO_BREAK_CHAR_TRANSMIT			(0ULL<<0)
#define	BREAK_CHAR_TRANSMIT				(1ULL<<0)


/*
 * USART_CR2
 * shift 16 bit more relative to manual
 */
#define	LIN_MODE_DISABLE				(0ULL<<30)
#define	LIN_MODE_ENABLE					(1ULL<<30)

#define	USART_1_STOP_BIT				(0ULL<<29)
#define	USART_0_5_STOP_BIT				(1ULL<<29)
#define	USART_2_STOP_BIT				(2ULL<<29)
#define	USART_1_5_STOP_BIT				(3ULL<<29)

#define	CK_PIN_DISABLE					(0ULL<<27)
#define	CK_PIN_ENABLE					(1ULL<<27)

#define	CPOL_CK_STEADY_LOW				(0ULL<<26)
#define	CPOL_CK_STEADY_HIGH				(1ULL<<26)

#define	CPHA_FIRST_EDGE					(0ULL<<25)
#define	CPHA_SECOND_EDGE				(1ULL<<25)


void usartConfig(USART *usart,uint64_t CR,UsartConfigData *usartConfigData);
void usartSend9Bit(USART *usart,uint16_t data);
#endif /* UART_H_ */
