/*
 * gpio.h
 *
 *  Created on: Oct 24, 2019
 *      Author: User
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct GPIOx GPIOx;
struct GPIOx{
	volatile	uint32_t	MODER;
	volatile	uint32_t	OTYPER;
	volatile	uint32_t	OSPEEDR;
	volatile	uint32_t	PUPDR;
	volatile	uint32_t	IDR;
	volatile	uint32_t	ODR;
	volatile	uint32_t	BSRR;
	volatile	uint32_t	LCKR;
	volatile	uint32_t	AFRL;
	volatile	uint32_t	AFRH;
};

void configGPIO(GPIOx *GPIO,uint32_t pin,uint32_t MODER,uint32_t OTYPER,uint32_t OSPEEDR,uint32_t PUPDR,uint32_t AFRLH);
void setResetGPIO(GPIOx *GPIO, uint32_t pin, bool on);
bool readGPIO(GPIOx *GPIO, uint32_t pin);
void toggleGPIO(GPIOx *GPIO, uint32_t pin);

#define	GPIOA	((GPIOx *)(0x40020000))
#define	GPIOB	((GPIOx *)(0x40020400))
#define	GPIOC	((GPIOx *)(0x40020800))
#define	GPIOD	((GPIOx *)(0x40020C00))
#define	GPIOE	((GPIOx *)(0x40021000))
#define	GPIOF	((GPIOx *)(0x40021400))
#define	GPIOG	((GPIOx *)(0x40021800))
#define	GPIOH	((GPIOx *)(0x40021C00))
#define	GPIOI	((GPIOx *)(0x40022000))
#define	GPIOJ	((GPIOx *)(0x40022400))
#define	GPIOK	((GPIOx *)(0x40022800))

/*
 * GPIOx_MODER
 */
#define	GPIO_INPUT			0
#define	GPIO_OUTPUT			1
#define	GPIO_ALT_FUNC		2
#define	GPIO_ANALOG			3

/*
 * GPIOx_OTYPER
 */
#define	OUTPUT_PUSH_PULL	0
#define	OUTPUT_OPEN_DRAIN	1

/*
 * GPIOx_OSPEEDR
 */
#define	LOW_SPEED			0
#define	MED_SPEED			1
#define	HIGH_SPEED			2
#define	VERY_HIGH_SPEED		3

/*
 * GPIOx_PUPDR
 */
#define	NO_PUPD				0
#define	PULL_UP				1
#define	PULL_DOWN			2

/*
 * GPIOx_AFRH
 */
#define	AF0			0
#define	AF1			1
#define	AF2			2
#define	AF3			3
#define	AF4			4
#define	AF5			5
#define	AF6			6
#define	AF7			7
#define	AF8			8
#define	AF9			9
#define	AF10		10
#define	AF11		11
#define	AF12		12
#define	AF13		13
#define	AF14		14
#define	AF15		15



#endif /* GPIO_H_ */
