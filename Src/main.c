/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "rcc.h"
#include "nvic.h"
#include "uart.h"
#include "gpio.h"
#include "state_machine.h"
#include "adc.h"
#include "queue.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
Queue execQueue,U1ISRQueue,U2ISRQueue,U3ISRQueue,U4ISRQueue,U6ISRQueue,ADCISRQueue;
Event *execEvent,*event1,*event2,*event3,*event4,*event6,*eventA;
uint32_t dataIndex1=0,dataIndex2=0,dataIndex3=0,dataIndex4=0,dataIndex6=0;
int interrupts[]={18,37,38,39,52,71,-1};
uint16_t data[]={6};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	volatile SMFuncPtr smFuncPtr;
	//master USART1 initialization
	//create queue for USART1 and USART2
	queueInit(&execQueue);
	queueInit(&U1ISRQueue);
	queueInit(&U2ISRQueue);
	queueInit(&U3ISRQueue);
	queueInit(&U4ISRQueue);
	queueInit(&U6ISRQueue);
	queueInit(&ADCISRQueue);
	//initialize for the state machine
	eventEnqueue(&execQueue,createEvent(START_EVENT,&slave2SM,0,data,RX_DATA));
	eventEnqueue(&execQueue,createEvent(START_EVENT,&slave3SM,0,data,RX_DATA));
	eventEnqueue(&execQueue,createEvent(START_EVENT,&slave6SM,0,data,RX_DATA));
	eventEnqueue(&execQueue,createEvent(START_EVENT,&master1SM,0,data,RX_DATA));

	//USART1, USART2, USART3, USART6 clock enable
	RCC->APB1RSTR |= (RCC_APB1RSTR_USART2RST | RCC_APB1RSTR_USART3RST);
	RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART2RST | RCC_APB1RSTR_USART3RST);
	RCC->APB1ENR |= (RCC_APB1ENR_USART2EN | RCC_APB1ENR_USART3EN);

	RCC->APB2RSTR |= (RCC_APB2RSTR_USART1RST | RCC_APB2RSTR_USART6RST)  ;
	RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST | RCC_APB2RSTR_USART6RST);
	RCC->APB2ENR |= (RCC_APB2ENR_USART1EN | RCC_APB2ENR_USART6EN);


	//GPIO clock enable
	RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOARST | RCC_AHB1RSTR_GPIOGRST \
			| RCC_AHB1RSTR_GPIOBRST | RCC_AHB1RSTR_GPIOCRST | RCC_AHB1RSTR_GPIODRST);
	RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOARST | RCC_AHB1RSTR_GPIOGRST \
			| RCC_AHB1RSTR_GPIOBRST | RCC_AHB1RSTR_GPIOCRST | RCC_AHB1RSTR_GPIODRST);
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOGEN \
			| RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN);


	RCC->APB2RSTR |= RCC_APB2RSTR_ADCRST;
	RCC->APB2RSTR &= ~(RCC_APB2RSTR_ADCRST);
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	int channelList[]={5,13,-1};

	configGPIOWithoutAF(GPIOA,5,GPIO_ANALOG,OUTPUT_PUSH_PULL,LOW_SPEED,NO_PUPD);
	configGPIOWithoutAF(GPIOC,3,GPIO_ANALOG,OUTPUT_PUSH_PULL,LOW_SPEED,NO_PUPD);



	adcConfig(ADC1, ADC_CR1_RES_12 | ADC_CR1_DISCEN | ADC_CR1_SCAN		\
			  | ADC_CR1_EOCIE | ADC_CR2_EOCS);

	adcSamplingTime(ADC1,5,_480_CYCLES);
	adcSamplingTime(ADC1,13,_480_CYCLES);
	adcSetChannelSequence(ADC1,&channelList);
	adcConfig(ADC1, ADC_CR2_ADON);

	//37:USART1
	//38:USART2
	//39:USART3
	//71:USART6
	nvicMultiEnableInterrupt(NVIC,interrupts);

	//master
	//AF7
	//USART1_TX	PA9
	//USART1_RX	PB7
	configGPIO(GPIOA,9,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);
	configGPIO(GPIOB,7,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);

	//slave
	//USART2_TX	PD5
	//USART2_RX	PA3
	configGPIO(GPIOD,5,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);
	configGPIO(GPIOA,3,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);

	//slave
	//USART3_TX	PB10
	//USART3_RX	PB11
	configGPIO(GPIOB,10,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);
	configGPIO(GPIOB,11,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);

	//slave
	//AF8
	//USART6_TX	PC6
	//USART6_RX	PC7
	configGPIO(GPIOC,6,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF8);
	configGPIO(GPIOC,7,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF8);

	//slave
	//AF8
	//UART4_TX	PC10
	//UART4_RX	PC11
	configGPIO(GPIOC,10,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF8);
	configGPIO(GPIOC,11,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF8);


	//USART1 configure (master)
	UsartConfigData usartConfigData;
	usartConfigData.baudrate = 9600;
	usartConfigData.peripheralFreq = 45000000;
	usartConfigData.muteModeAdress = 0;
	usartConfig(USART1,WORD_9_BIT_DATA | RXNE_IT 			\
			| TRANSMIT_ENABLE | RECEIVER_ENABLE				\
			,&usartConfigData);
	usartCR1(USART1,USART_ENABLE);


	//USART2 configure (slave)
	UsartConfigData usartConfigData1;
	usartConfigData1.baudrate = 9600;
	usartConfigData1.peripheralFreq = 45000000;
	usartConfigData1.muteModeAdress = 1;
	usartConfig(USART2,WORD_9_BIT_DATA | RXNE_IT 			\
		    | TRANSMIT_ENABLE | RECEIVER_ENABLE				\
		    | WAKE_ADDRESS_MARK | RWU_RECEIVER_MUTE_MODE	\
			,&usartConfigData1);
	usartCR1(USART2,USART_ENABLE);


	//USART3 configure (slave)
	UsartConfigData usartConfigData2;
	usartConfigData2.baudrate = 9600;
	usartConfigData2.peripheralFreq = 45000000;
	usartConfigData2.muteModeAdress = 2;
	usartConfig(USART3,WORD_9_BIT_DATA | RXNE_IT 			\
		    | TRANSMIT_ENABLE | RECEIVER_ENABLE				\
		    | WAKE_ADDRESS_MARK | RWU_RECEIVER_MUTE_MODE	\
			,&usartConfigData2);
	usartCR1(USART3,USART_ENABLE);



	//USART6 configure (slave)
	UsartConfigData usartConfigData3;
	usartConfigData3.baudrate = 9600;
	usartConfigData3.peripheralFreq = 45000000;
	usartConfigData3.muteModeAdress = 3;
	usartConfig(USART6,WORD_9_BIT_DATA | RXNE_IT 			\
		    | TRANSMIT_ENABLE | RECEIVER_ENABLE				\
		    | WAKE_ADDRESS_MARK | RWU_RECEIVER_MUTE_MODE	\
			,&usartConfigData3);
	usartCR1(USART6,USART_ENABLE);

	//UART4 configure (slave)
	UsartConfigData usartConfigData4;
	usartConfigData4.baudrate = 9600;
	usartConfigData4.peripheralFreq = 45000000;
	usartConfigData4.muteModeAdress = 0;
	usartConfig(UART4,WORD_9_BIT_DATA | RXNE_IT 			\
			| TRANSMIT_ENABLE | RECEIVER_ENABLE				\
			,&usartConfigData4);
	usartCR1(UART4,USART_ENABLE);
	/*
	 * PG13	green LED
	 * PA0	blue button
	 */
	configGPIOWithoutAF(GPIOA,0,GPIO_INPUT,0,VERY_HIGH_SPEED,PULL_DOWN);
	configGPIOWithoutAF(GPIOG,13,GPIO_OUTPUT,OUTPUT_PUSH_PULL			\
				,HIGH_SPEED,NO_PUPD);
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(getQueueSize(&execQueue)!=0){
		  execEvent=eventDequeue(&execQueue);
		  smFuncPtr=execEvent->smFuncPtr;
		  smFuncPtr(execEvent);
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 90;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

void USART1_IRQHandler(void){
	event1=isrUsartEvent(USART1,&U1ISRQueue,event1,&dataIndex1);
}

void USART2_IRQHandler(void){
	event2=isrUsartEvent(USART2,&U2ISRQueue,event2,&dataIndex2);
}

void USART3_IRQHandler(void){
	event3=isrUsartEvent(USART3,&U3ISRQueue,event3,&dataIndex3);
}

void USART6_IRQHandler(void){
	event6=isrUsartEvent(USART6,&U6ISRQueue,event6,&dataIndex6);
}

void UART4_IRQHandler(void){
	event4=isrUsartEvent(UART4,&U4ISRQueue,event4,&dataIndex4);
}
void ADC_IRQHandler(void){
	eventA=eventDequeue(&ADCISRQueue);
	eventA->data[0] = (uint32_t)(ADC1->DR);
	eventEnqueue(&execQueue,eventA);
	//release event
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
