#include "unity.h"
#include "state_machine.h"
#include "mock_uart.h"

void setUp(void)
{
}

void tearDown(void)
{
}
//void usartSend9Bit_Expect(USART *usart,uint16_t data);
//void enqueue_Expect(Queue* queue, int item);
//int dequeue_ExpectAndReturn(Queue* queue);

void test_stateMachine_testOneCycle(void)
{
  SMInfo smInfo;
  smInfo.masterState = READ_BUTTON;
  smInfo.ReadFlag = false;
  smInfo.buttonState = 0b00000000;
  smInfo.rgbState = 0b00000000;
  usartSend9Bit_Expect(USART1,0b100100001);
  usartSend9Bit_Expect(USART1,0b000000001);
  stateMachine(USART1, &smInfo);
  TEST_ASSERT_EQUAL(CONTROL_LED,smInfo.masterState);
  TEST_ASSERT_EQUAL(0b00000000,smInfo.buttonState);
  TEST_ASSERT_EQUAL(0b00000000,smInfo.rgbState);
  TEST_ASSERT_EQUAL(false,smInfo.ReadFlag);

  smInfo.buttonState = 0b00000001;
  usartSend9Bit_Expect(USART1,0b100100010);
  usartSend9Bit_Expect(USART1,0b000000001);
  stateMachine(USART1, &smInfo);
  TEST_ASSERT_EQUAL(PROBE,smInfo.masterState);
  TEST_ASSERT_EQUAL(0b00000001,smInfo.buttonState);
  TEST_ASSERT_EQUAL(0b00000001,smInfo.rgbState);
  TEST_ASSERT_EQUAL(false,smInfo.ReadFlag);

  usartSend9Bit_Expect(USART1,0b100100011);
  usartSend9Bit_Expect(USART1,0b000000001);
  usartSend9Bit_Expect(USART1,0b000000001);
  stateMachine(USART1, &smInfo);
  TEST_ASSERT_EQUAL(READ_BUTTON,smInfo.masterState);
  TEST_ASSERT_EQUAL(0b00000001,smInfo.buttonState);
  TEST_ASSERT_EQUAL(0b00000001,smInfo.rgbState);
  TEST_ASSERT_EQUAL(false,smInfo.ReadFlag);

  usartSend9Bit_Expect(USART1,0b100100001);
  usartSend9Bit_Expect(USART1,0b000000001);
  stateMachine(USART1, &smInfo);
  TEST_ASSERT_EQUAL(CONTROL_LED,smInfo.masterState);
  TEST_ASSERT_EQUAL(false,smInfo.ReadFlag);
}

void test_stateMachine_testOneCycle_differentButtonState(void)
{
  SMInfo smInfo;
  smInfo.masterState = READ_BUTTON;
  smInfo.ReadFlag = false;
  smInfo.buttonState = 0b00000000;
  smInfo.rgbState = 0b00000000;
  usartSend9Bit_Expect(USART1,0b100100001);
  usartSend9Bit_Expect(USART1,0b000000001);
  stateMachine(USART1, &smInfo);
  TEST_ASSERT_EQUAL(CONTROL_LED,smInfo.masterState);
  TEST_ASSERT_EQUAL(0b00000000,smInfo.buttonState);
  TEST_ASSERT_EQUAL(0b00000000,smInfo.rgbState);
  TEST_ASSERT_EQUAL(false,smInfo.ReadFlag);

  smInfo.buttonState = 0b00000000;
  usartSend9Bit_Expect(USART1,0b100100010);
  usartSend9Bit_Expect(USART1,0b000000000);
  stateMachine(USART1, &smInfo);
  TEST_ASSERT_EQUAL(PROBE,smInfo.masterState);
  TEST_ASSERT_EQUAL(0b00000000,smInfo.buttonState);
  TEST_ASSERT_EQUAL(0b00000000,smInfo.rgbState);
  TEST_ASSERT_EQUAL(false,smInfo.ReadFlag);

  usartSend9Bit_Expect(USART1,0b100100011);
  usartSend9Bit_Expect(USART1,0b000000000);
  usartSend9Bit_Expect(USART1,0b000000000);
  stateMachine(USART1, &smInfo);
  TEST_ASSERT_EQUAL(READ_BUTTON,smInfo.masterState);
  TEST_ASSERT_EQUAL(0b00000000,smInfo.buttonState);
  TEST_ASSERT_EQUAL(0b00000000,smInfo.rgbState);
  TEST_ASSERT_EQUAL(false,smInfo.ReadFlag);

  usartSend9Bit_Expect(USART1,0b100100001);
  usartSend9Bit_Expect(USART1,0b000000001);
  stateMachine(USART1, &smInfo);
  TEST_ASSERT_EQUAL(CONTROL_LED,smInfo.masterState);
  TEST_ASSERT_EQUAL(false,smInfo.ReadFlag);
}
