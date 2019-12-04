/*
 * state_machine.c
 *
 *  Created on: Nov 5, 2019
 *      Author: User
 */

#include "state_machine.h"
#include "uart.h"

void stateMachine(USART *usart,SMInfo *smInfo){

  switch(smInfo->masterState){
    case READ_BUTTON:
    	usartSend9Bit(usart,0b100100001);//address
    	usartSend9Bit(usart,0b000000001);//command
      smInfo->masterState = CONTROL_LED;
    	break;
    case CONTROL_LED:
      smInfo->ReadFlag = true;
      usartSend9Bit(usart,0b100100010);//address
      usartSend9Bit(usart,0xff & (smInfo->buttonState));//led depend on button
      smInfo->rgbState = smInfo->buttonState;
      smInfo->ReadFlag = false;
      smInfo->masterState = PROBE;
    	break;
    case PROBE:
      smInfo->ReadFlag = true;
      usartSend9Bit(usart,0b100100011);//address
      usartSend9Bit(usart,0xff & (smInfo->rgbState));
      usartSend9Bit(usart,0xff & (smInfo->buttonState));
      smInfo->ReadFlag = false;
      smInfo->masterState = READ_BUTTON;
    	break;
  }

}
