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
//SMInfo smInfo;
Info U1Info,U2Info,U3Info,U6Info,adcInfo;
Queue usart1TXQ,usart2TXQ,usart3TXQ,usart6TXQ;
SMInfo smInfo,smInfoOut;
Queue smQueue;
volatile int interrupts[]={18,37,38,39,71,-1};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	//master USART1 initialization
	//create queue for USART1 and USART2
	queueInit(&usart1TXQ,sizeof(uint16_t));
	queueInit(&usart2TXQ,sizeof(uint16_t));
	queueInit(&usart3TXQ,sizeof(uint16_t));
	queueInit(&usart6TXQ,sizeof(uint16_t));
	queueInit(&smQueue,sizeof(SMInfo));

	//initialize adc state
	adcInfo.state=ADC5;

	//initialize for the state machine
	U1Info.state = READ_BUTTON;
	U1Info.ReadFlag = false;
	U1Info.ledState = 0;
	U1Info.buttonState = 0;


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

	nvicEnableInterrupt(NVIC,18);

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
	nvicEnableInterrupt(NVIC,37);
	nvicEnableInterrupt(NVIC,38);
	nvicEnableInterrupt(NVIC,39);
	nvicEnableInterrupt(NVIC,71);

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
	  if(getQueueSize(&smQueue)==0){
		  stateMachineV2(&U1Info,&usart1TXQ);
	  }else{
		  dequeue(&smQueue,&smInfoOut);
		  stateMachineV2(smInfoOut.info,smInfoOut.usartQueue);
	  }

	  HAL_Delay(15);
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

uint16_t U1Msg=0;
void USART1_IRQHandler(void){
	if(USART1->SR & USART_READY_TO_READ){
		U1Msg = (uint16_t)(0x1ff & USART1->DR);
		if(U1Info.ReadFlag == false){
			U1Info.buttonState = U1Msg;
		}
	}else if(USART1->SR & TRANSMIT_COMPLETE){
		ITDequeue(USART1,&usart1TXQ);
	}
}

void USART2_IRQHandler(void){
	if(USART2->SR & USART_READY_TO_READ){
		U2Info.message = (uint16_t)(0x1ff & USART2->DR);
		checkAddressV2(&U2Info,0b100100001,U2_MATCH_ADDRESS);

		//stateMachineV2(&U2Info,&usart2TXQ);


		nvicMultiDisableInterrupt(NVIC,interrupts);
		smInfo.info=(&U2Info);
		smInfo.usartQueue=(&usart2TXQ);
		enqueue(&smQueue,&smInfo);
		nvicMultiEnableInterrupt(NVIC,interrupts);

	}else if(USART2->SR & TRANSMIT_COMPLETE){
		ITDequeue(USART2,&usart2TXQ);
	}
}

void USART3_IRQHandler(void){
	U3Info.message = (uint16_t)(0x1ff & USART3->DR);
	checkAddressV2(&U3Info,0b100100010,U3_MATCH_ADDRESS);

	//stateMachineV2(&U3Info,&usart3TXQ);
	nvicMultiDisableInterrupt(NVIC,interrupts);
	smInfo.info=(&U3Info);
	smInfo.usartQueue=(&usart3TXQ);
	enqueue(&smQueue,&smInfo);
	nvicMultiEnableInterrupt(NVIC,interrupts);


}

void USART6_IRQHandler(void){
	if(USART6->SR & USART_READY_TO_READ){
		U6Info.message = (uint16_t)(0x1ff & USART6->DR);
		checkAddressV2(&U6Info,0b100100011,U6_MATCH_ADDRESS);

		//stateMachineV2(&U6Info,&usart6TXQ);


		nvicMultiDisableInterrupt(NVIC,interrupts);
		smInfo.info=(&U6Info);
		smInfo.usartQueue=(&usart6TXQ);
		enqueue(&smQueue,&smInfo);
		nvicMultiEnableInterrupt(NVIC,interrupts);

	}else if(USART6->SR & TRANSMIT_COMPLETE){
		ITDequeue(USART6,&usart6TXQ);
	}
}

void ADC_IRQHandler(void){
	adcInfo.adcData = (uint32_t)(ADC1->DR);

	nvicMultiDisableInterrupt(NVIC,interrupts);
	smInfo.info=(&adcInfo);
	enqueue(&smQueue,&smInfo);
	nvicMultiEnableInterrupt(NVIC,interrupts);

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
