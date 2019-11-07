/*
 * gpio.c
 *
 *  Created on: Oct 24, 2019
 *      Author: User
 */

#include "gpio.h"

void configGPIO(GPIOx *GPIO,uint8_t pin,uint8_t MODER,		\
	uint8_t OTYPER,uint8_t OSPEEDR,uint8_t PUPDR,uint8_t AFRLH){
	GPIO->MODER |= (uint32_t)(MODER<<(pin*2));
	GPIO->OTYPER |=(uint32_t)(OTYPER<<pin);
	GPIO->OSPEEDR |=(uint32_t)(OSPEEDR<<(pin*2));
	GPIO->PUPDR |=(uint32_t)(PUPDR<<(pin*2));
	if(pin<=7)
		GPIO->AFRL |=(uint32_t)(AFRLH<<(pin*4));
	else
		GPIO->AFRH |=(uint32_t)(AFRLH<<((pin-8)*4));
}
