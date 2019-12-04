/*
 * gpio.c
 *
 *  Created on: Oct 24, 2019
 *      Author: User
 */

#include "gpio.h"

void configGPIO(GPIOx *GPIO,uint32_t pin,uint32_t MODER,		\
		uint32_t OTYPER,uint32_t OSPEEDR,uint32_t PUPDR,uint32_t AFRLH){


	GPIO->MODER &= ~(3<<(pin*2));
	GPIO->MODER |= (uint32_t)(MODER<<(pin*2));

	GPIO->OTYPER |=(uint32_t)(OTYPER<<pin);

	GPIO->OSPEEDR &= ~(3<<(pin*2));
	GPIO->OSPEEDR |=(uint32_t)(OSPEEDR<<(pin*2));

	GPIO->PUPDR &= ~(3<<(pin*2));
	GPIO->PUPDR |=(uint32_t)(PUPDR<<(pin*2));

	if(pin<=7){
		GPIO->AFRL &= ~(15<<(pin*4));
		GPIO->AFRL |=(uint32_t)(AFRLH<<(pin*4));
	}
	else{
		GPIO->AFRH &= ~(15<<((pin-8)*4));
		GPIO->AFRH |=(uint32_t)(AFRLH<<((pin-8)*4));
	}
}

void configGPIOWithoutAF(GPIOx *GPIO,uint32_t pin,uint32_t MODER,		\
		uint32_t OTYPER,uint32_t OSPEEDR,uint32_t PUPDR){
	GPIO->MODER &= ~(3<<(pin*2));
	GPIO->MODER |= (uint32_t)(MODER<<(pin*2));

	GPIO->OTYPER |=(uint32_t)(OTYPER<<pin);

	GPIO->OSPEEDR &= ~(3<<(pin*2));
	GPIO->OSPEEDR |=(uint32_t)(OSPEEDR<<(pin*2));

	GPIO->PUPDR &= ~(3<<(pin*2));
	GPIO->PUPDR |=(uint32_t)(PUPDR<<(pin*2));
}


void setResetGPIO(GPIOx *GPIO, uint32_t pin, bool on){
	if(on==true){
		GPIO->BSRR |=(uint32_t)(1<<pin);
	}
	else{
		GPIO->BSRR |=(uint32_t)(1<<(pin+16));
	}
}

bool readGPIO(GPIOx *GPIO, uint32_t pin){
	if(GPIO->IDR & (1<<pin)){
		return true;
	}
	else{
		return false;
	}
}

void toggleGPIO(GPIOx *GPIO, uint32_t pin){
	if(GPIO->ODR & (1<<pin)){
		setResetGPIO(GPIO,pin,false);
	}
	else{
		setResetGPIO(GPIO,pin,true);
	}
}


