#include "unity.h"
#include "nvic.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_nvicMultiEnableInterrupt(void)
{
    int interruptNums [] = {5,6,43,-1};
    NvicRegs nvicRegs;
    nvicRegs.ISER[0]=0;
    nvicRegs.ISER[1]=0;
    nvicMultiEnableInterrupt(&nvicRegs,interruptNums);
    TEST_ASSERT_EQUAL(0b1100000,nvicRegs.ISER[0]);
    TEST_ASSERT_EQUAL(0b100000000000,nvicRegs.ISER[1]);
}


void test_nvicMultiDisableInterrupt(void)
{
    int interruptNums [] = {5,6,43,-1};
    NvicRegs nvicRegs;
    nvicRegs.ICER[0]=0;
    nvicRegs.ICER[1]=0;
    nvicMultiDisableInterrupt(&nvicRegs,interruptNums);
    TEST_ASSERT_EQUAL(0b1100000,nvicRegs.ISER[0]);
    TEST_ASSERT_EQUAL(0b100000000000,nvicRegs.ISER[1]);
}
