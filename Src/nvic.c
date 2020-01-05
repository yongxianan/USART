/*
 * nvic.c
 *
 *  Created on: Oct 29, 2019
 *      Author: User
 */

#include "NVIC.h"

void nvicMultiEnableInterrupt(NvicRegs *nvic,int *interruptNumber){
	int i=0;
	while(interruptNumber[i]!=-1){
		nvicEnableInterrupt(nvic,interruptNumber[i]);
		i++;
	}
}
void nvicMultiDisableInterrupt(NvicRegs *nvic,int *interruptNumber){
	int i=0;
	while(interruptNumber[i]!=-1){
		nvicDisableInterrupt(nvic,interruptNumber[i]);
		i++;
	}
}

void nvicEnableInterrupt(NvicRegs *nvic, int interruptNumber){
	int n, bit;
	n = interruptNumber/32;
	bit = interruptNumber%32;
	nvic-> ISER[n] |= (1 << bit);
}


void nvicDisableInterrupt(NvicRegs *nvic,int interruptNumber){
	int n, bit;
	n = interruptNumber/32;
	bit = interruptNumber%32;
	nvic-> ICER[n] |= (1 << bit);
}


void nvicEnablePendingInterrupt(NvicRegs *nvic,int interruptNumber){
	int n, bit;
	n = interruptNumber/32;
	bit = interruptNumber%32;
	nvic-> ISPR[n] |= (1 << bit);
}



void nvicDisablePendingInterrupt(NvicRegs *nvic,int interruptNumber){
	int n, bit;
	n = interruptNumber/32;
	bit = interruptNumber%32;
	nvic-> ICPR[n]  |= (1 << bit);
}



/**
 * Find out if interrupt is active.
 *
 * Return :
 * 	0			means not active
 * 	non-zero 	means active*/
int nvicIsInterruptActive(NvicRegs *nvic,int interruptNumber){
	int n, bit;
	n = interruptNumber/32;
	bit = interruptNumber%32;

	return (nvic-> IABR[n]) << bit;
}
