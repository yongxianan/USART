#include "unity.h"
#include "state_machine.h"
#include "mock_uart.h"
#include "mock_gpio.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//void stateMachineV2(Info *info,)
void test_stateMachineV2_USART2_SENDBACK_BUTTON(void){
  Info U2Info;
  Queue usartTXQ;
  U2Info.message = 0b100100001;
  U2Info.state = U2_MATCH_ADDRESS;
  stateMachineV2(&U2Info,&usartTXQ);

  TEST_ASSERT_EQUAL(SENDBACK_BUTTON,U2Info.state);
  U2Info.message = 0b000000001;
  readGPIO_ExpectAndReturn(GPIOA,0,true);
  usartSend9BitV2_Expect(USART2,&usartTXQ,0b000000001);
  stateMachineV2(&U2Info,&usartTXQ);

  TEST_ASSERT_EQUAL(CHECK_ADDR,U2Info.state);
}

void test_stateMachineV2_USART3_SET_LED(void){
  Info U3Info;
  Queue usartTXQ;
  U3Info.message = 0b100100010;
  U3Info.state = U3_MATCH_ADDRESS;
  stateMachineV2(&U3Info,&usartTXQ);

  TEST_ASSERT_EQUAL(SET_LED,U3Info.state);
  U3Info.message = 0b000000001;
  setResetGPIO_Expect(GPIOG,13,0x1);
  stateMachineV2(&U3Info,&usartTXQ);

  TEST_ASSERT_EQUAL(CHECK_ADDR,U3Info.state);
}

void test_stateMachineV2_USART6_PROBE(void){
  Info U6Info;
  Queue usartTXQ;
  U6Info.message = 0b100100011;
  U6Info.state = U6_MATCH_ADDRESS;
  stateMachineV2(&U6Info,&usartTXQ);

  TEST_ASSERT_EQUAL(PROBE_LED,U6Info.state);
  U6Info.message = 0b000000001;
  //usartSend9BitV2_Expect(USART6,0b000000001);
  stateMachineV2(&U6Info,&usartTXQ);

  TEST_ASSERT_EQUAL(PROBE_BUTTON,U6Info.state);
  U6Info.message = 0b000000001;
  //usartSend9BitV2_Expect(USART6,0b000000001);
  stateMachineV2(&U6Info,&usartTXQ);

  TEST_ASSERT_EQUAL(CHECK_ADDR,U6Info.state);
}

void test_stateMachineV2_USART6_CHECK_ADDR(void){
  Info U6Info;
  Queue usartTXQ;
  U6Info.message = 0b111111111;
  U6Info.state = CHECK_ADDR;
  stateMachineV2(&U6Info,&usartTXQ);

  TEST_ASSERT_EQUAL(CHECK_ADDR,U6Info.state);
}

void test_stateMachineV2_USART1(void){
  Info U1Info;
  Queue usartTXQ;
  U1Info.message = 0b111111111;
  U1Info.state = READ_BUTTON;
  U1Info.buttonState = 0b00000000;
  U1Info.ledState = 0b00000000;
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b100100001);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000001);//check button commands
  stateMachineV2(&U1Info,&usartTXQ);

  TEST_ASSERT_EQUAL(CONTROL_LED,U1Info.state);
  TEST_ASSERT_EQUAL(0b00000000,U1Info.buttonState);
  TEST_ASSERT_EQUAL(0b00000000,U1Info.ledState);
  TEST_ASSERT_EQUAL(false,U1Info.ReadFlag);
  U1Info.buttonState = 0b00000001;
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b100100010);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000001);
  stateMachineV2(&U1Info,&usartTXQ);

  TEST_ASSERT_EQUAL(PROBE,U1Info.state);
  TEST_ASSERT_EQUAL(0b00000001,U1Info.buttonState);
  TEST_ASSERT_EQUAL(0b00000001,U1Info.ledState);
  TEST_ASSERT_EQUAL(false,U1Info.ReadFlag);

  usartSend9BitV2_Expect(USART1,&usartTXQ,0b100100011);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000001);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000001);
  stateMachineV2(&U1Info,&usartTXQ);

  TEST_ASSERT_EQUAL(READ_BUTTON,U1Info.state);
  TEST_ASSERT_EQUAL(0b00000001,U1Info.buttonState);
  TEST_ASSERT_EQUAL(0b00000001,U1Info.ledState);
  TEST_ASSERT_EQUAL(false,U1Info.ReadFlag);

  usartSend9BitV2_Expect(USART1,&usartTXQ,0b100100001);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000001);
  stateMachineV2(&U1Info,&usartTXQ);
  TEST_ASSERT_EQUAL(CONTROL_LED,U1Info.state);
  TEST_ASSERT_EQUAL(false,U1Info.ReadFlag);
}

void test_stateMachineV2_USART1_differentButtonState(void){
  Info U1Info;
  Queue usartTXQ;
  U1Info.message = 0b111111111;
  U1Info.state = READ_BUTTON;
  U1Info.buttonState = 0b00000000;
  U1Info.ledState = 0b00000000;
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b100100001);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000001);//check button commands
  stateMachineV2(&U1Info,&usartTXQ);

  TEST_ASSERT_EQUAL(CONTROL_LED,U1Info.state);
  TEST_ASSERT_EQUAL(0b00000000,U1Info.buttonState);
  TEST_ASSERT_EQUAL(0b00000000,U1Info.ledState);
  TEST_ASSERT_EQUAL(false,U1Info.ReadFlag);
  U1Info.buttonState = 0b00000000;
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b100100010);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000000);
  TEST_ASSERT_EQUAL(false,U1Info.ReadFlag);
  stateMachineV2(&U1Info,&usartTXQ);

  TEST_ASSERT_EQUAL(PROBE,U1Info.state);
  TEST_ASSERT_EQUAL(0b00000000,U1Info.buttonState);
  TEST_ASSERT_EQUAL(0b00000000,U1Info.ledState);
  TEST_ASSERT_EQUAL(false,U1Info.ReadFlag);

  usartSend9BitV2_Expect(USART1,&usartTXQ,0b100100011);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000000);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000000);
  stateMachineV2(&U1Info,&usartTXQ);

  TEST_ASSERT_EQUAL(READ_BUTTON,U1Info.state);
  TEST_ASSERT_EQUAL(0b00000000,U1Info.buttonState);
  TEST_ASSERT_EQUAL(0b00000000,U1Info.ledState);
  TEST_ASSERT_EQUAL(false,U1Info.ReadFlag);

  usartSend9BitV2_Expect(USART1,&usartTXQ,0b100100001);
  usartSend9BitV2_Expect(USART1,&usartTXQ,0b000000001);
  stateMachineV2(&U1Info,&usartTXQ);
  TEST_ASSERT_EQUAL(CONTROL_LED,U1Info.state);
  TEST_ASSERT_EQUAL(false,U1Info.ReadFlag);
}
