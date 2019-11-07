#include "unity.h"
#include "gpio.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_gpio_config(void)
{

  GPIOx gpio;

  gpio.MODER=0;
  gpio.OTYPER=0;
  gpio.OSPEEDR=0;
  gpio.PUPDR=0;
  gpio.AFRH=0;
  gpio.AFRL=0;

  configGPIO(&gpio,9,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL     \
      ,HIGH_SPEED,NO_PUPD,AF7);
  TEST_ASSERT_EQUAL_HEX(0b10000000000000000000,gpio.MODER);
  TEST_ASSERT_EQUAL_HEX(0b0,gpio.OTYPER);
  TEST_ASSERT_EQUAL_HEX(0b10000000000000000000,gpio.OSPEEDR);
  TEST_ASSERT_EQUAL_HEX(0b0,gpio.PUPDR);
  //AF7 written on AFRH due to pin 9
  TEST_ASSERT_EQUAL_HEX(0b1110000,gpio.AFRH);
  TEST_ASSERT_EQUAL_HEX(0b0,gpio.AFRL);
}

void test_gpio_config_test_AFRL_got_data(void)
{
  GPIOx gpio;
  gpio.MODER=0;
  gpio.OTYPER=0;
  gpio.OSPEEDR=0;
  gpio.PUPDR=0;
  gpio.AFRH=0;
  gpio.AFRL=0;
  
  configGPIO(&gpio,2,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL     \
      ,HIGH_SPEED,NO_PUPD,AF7);
  TEST_ASSERT_EQUAL_HEX(0b100000,gpio.MODER);
  TEST_ASSERT_EQUAL_HEX(0b0,gpio.OTYPER);
  TEST_ASSERT_EQUAL_HEX(0b100000,gpio.OSPEEDR);
  TEST_ASSERT_EQUAL_HEX(0b0,gpio.PUPDR);
  TEST_ASSERT_EQUAL_HEX(0b0,gpio.AFRH);
  TEST_ASSERT_EQUAL_HEX(0b11100000000,gpio.AFRL);
}
