/*
 * state_machine.h
 *
 *  Created on: Nov 5, 2019
 *      Author: User
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_
#include <stdbool.h>
#include "uart.h"

typedef enum{
  READ_BUTTON,
  CONTROL_LED,
  PROBE
}MasterState;

typedef struct{
  bool ReadFlag;
  uint8_t buttonState;
  uint8_t rgbState;
  MasterState masterState;//interrput won't touch masterState
}SMInfo;

void stateMachine(USART *usart, SMInfo *smInfo);

#endif /* STATE_MACHINE_H_ */
