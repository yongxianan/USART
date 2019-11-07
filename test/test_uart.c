#include "unity.h"
#include "uart.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_usartConfigBaudrate(void)
{
  USART usart1;
  UsartConfigData usartConfigData;
  usartConfigData.baudrate = 9600;
  usartConfigData.peripheralFreq = 72000000;
  usartConfig(&usart1,WORD_9_BIT_DATA | RXNE_IT 		\
    | TRANSMIT_ENABLE | RECEIVER_ENABLE			      \
    | USART_ENABLE, &usartConfigData);
  TEST_ASSERT_EQUAL(0x1D4C,usart1.BRR);
  TEST_ASSERT_EQUAL(0b11000000101100,usart1.CR1);
  TEST_ASSERT_EQUAL(0b0,usart1.CR2);
  TEST_ASSERT_EQUAL(0b0,usart1.CR3);
}

void test_configMultiProcessorSetMuteModeAddress(void)
{
  USART usart1;
  UsartConfigData usartConfigData;
  usartConfigData.muteModeAdress = 9;

  usartConfig(&usart1,WAKE_ADDRESS_MARK | 	       \
    RWU_RECEIVER_MUTE_MODE,&usartConfigData);
  TEST_ASSERT_EQUAL(0b100000000010,usart1.CR1);
  TEST_ASSERT_EQUAL(0b1001,usart1.CR2);
  TEST_ASSERT_EQUAL(0b0,usart1.CR3);
}

void test_usartConfig(void){
  USART usart1;
  UsartConfigData usartConfigData;
  usartConfigData.baudrate = 9600;
  usartConfigData.peripheralFreq = 72000000;
  usartConfigData.muteModeAdress = 9;

  usartConfig(&usart1,WORD_9_BIT_DATA | RXNE_IT 		\
    | TRANSMIT_ENABLE | RECEIVER_ENABLE			        \
    | USART_ENABLE | WAKE_ADDRESS_MARK     	        \
    | RWU_RECEIVER_MUTE_MODE,&usartConfigData);
  TEST_ASSERT_EQUAL(0b11100000101110,usart1.CR1);
  TEST_ASSERT_EQUAL(0b1001,usart1.CR2);
  TEST_ASSERT_EQUAL(0b0,usart1.CR3);
}
