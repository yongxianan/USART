/*
 * nvic.h
 *
 *  Created on: Oct 29, 2019
 *      Author: User
 */

#ifndef NVIC_H_
#define NVIC_H_

#include <stdint.h>
typedef volatile uint32_t NVICRegister;

typedef struct NvicRegs NvicRegs;
struct NvicRegs{
	NVICRegister ISER[3];
	NVICRegister reversed0[29];
	NVICRegister ICER[3];
	NVICRegister reversed1[29];
	NVICRegister ISPR[3];
	NVICRegister reversed2[29];
	NVICRegister ICPR[3];
	NVICRegister reversed3[29];
	NVICRegister IABR[3];
	NVICRegister reversed4[61];
	NVICRegister IPR[21];
	NVICRegister reversed5[677];
	NVICRegister STIR;
};

#define nvic 	((NvicRegs *)0xE000E100)


void nvicEnableInterrupt(int interruptNumber);
void nvicDisableInterrupt(int interruptNumber);
int nvicIsInterruptActive(int interruptNumber);


#endif /* NVIC_H_ */
