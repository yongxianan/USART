/*
 * state_machine.c
 *
 *  Created on: Nov 5, 2019
 *      Author: User
 */

void stateMachineUsart(void){

  typedef enum{
		state1,
		state2,
		state3
	}StateMachine;

	static StateMachine stateMachine = state1;

  switch(stateMachine){
    case state1:
    	break;
    case state2:
    	break;
    case state3:
    	break;
  }

}
