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


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	//USART1, USART2, USART3, USART6 clock enable
	RCC->APB1RSTR |= (RCC_APB1RSTR_USART2RST | RCC_APB1RSTR_USART3RST);
	RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART2RST | RCC_APB1RSTR_USART3RST);
	RCC->APB1ENR |= (RCC_APB1ENR_USART2EN | RCC_APB1ENR_USART3EN);

	RCC->APB2RSTR |= (RCC_APB2RSTR_USART1RST | RCC_APB2RSTR_USART6RST)  ;
	RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST | RCC_APB2RSTR_USART6RST);
	RCC->APB2ENR |= (RCC_APB2ENR_USART1EN | RCC_APB2ENR_USART6EN);


	//GPIO clock enable
	RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOARST;
	RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOARST);
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN);


	//37:USART1
	//38:USART2
	//39:USART3
	//71:USART6
	nvicEnableInterrupt(37);
	nvicEnableInterrupt(38);
	nvicEnableInterrupt(39);
	nvicEnableInterrupt(71);


	//AF7
	//USART1_TX	PA9
	//USART1_RX	PA10
	configGPIO(GPIOA,9,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);
	configGPIO(GPIOA,10,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);


	//USART2_TX	PA2
	//USART2_RX	PA3
	configGPIO(GPIOA,2,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);
	configGPIO(GPIOA,3,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);


	//USART3_TX	PB10
	//USART3_RX	PB11
	configGPIO(GPIOB,10,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);
	configGPIO(GPIOB,11,GPIO_ALT_FUNC,OUTPUT_PUSH_PULL			\
		,VERY_HIGH_SPEED,NO_PUPD,AF7);


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
	usartConfigData.peripheralFreq = 72000000;
	usartConfig(USART1,WORD_9_BIT_DATA | RXNE_IT 		\
			| TRANSMIT_ENABLE | RECEIVER_ENABLE			\
			,&usartConfigData);
	usartCR1(USART1,USART_ENABLE);


	//USART2 configure (slave)
	UsartConfigData usartConfigData1;
	usartConfigData1.baudrate = 9600;
	usartConfigData1.peripheralFreq = 72000000;
	usartConfigData1.muteModeAdress = 1;
	usartConfig(USART2,WORD_9_BIT_DATA | RXNE_IT 			\
		    | TRANSMIT_ENABLE | RECEIVER_ENABLE				\
		    | WAKE_ADDRESS_MARK | RWU_RECEIVER_MUTE_MODE	\
			,&usartConfigData1);
	usartCR1(USART2,USART_ENABLE);


	//USART3 configure (slave)
	UsartConfigData usartConfigData2;
	usartConfigData2.baudrate = 9600;
	usartConfigData2.peripheralFreq = 72000000;
	usartConfigData2.muteModeAdress = 2;
	usartConfig(USART3,WORD_9_BIT_DATA | RXNE_IT 			\
		    | TRANSMIT_ENABLE | RECEIVER_ENABLE				\
		    | WAKE_ADDRESS_MARK | RWU_RECEIVER_MUTE_MODE	\
			,&usartConfigData2);
	usartCR1(USART3,USART_ENABLE);



	//USART6 configure (slave)
	UsartConfigData usartConfigData3;
	usartConfigData3.baudrate = 9600;
	usartConfigData3.peripheralFreq = 72000000;
	usartConfigData3.muteModeAdress = 3;
	usartConfig(USART6,WORD_9_BIT_DATA | RXNE_IT 			\
		    | TRANSMIT_ENABLE | RECEIVER_ENABLE				\
		    | WAKE_ADDRESS_MARK | RWU_RECEIVER_MUTE_MODE	\
			,&usartConfigData3);
	usartCR1(USART6,USART_ENABLE);
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
	  //stateMachine(USART *usart,SMInfo *smInfo);
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
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
uint16_t U2Msg=0;
void USART1_IRQHandler(void){
	if(USART1->SR & USART_READY_TO_READ){
		U1Msg = (uint16_t)(0x1ff & USART1->DR);
	}
	//if()
}

void USART2_IRQHandler(void){
	if(USART2->SR & USART_READY_TO_READ){
		U2Msg= (uint16_t)(USART2->DR);
	}
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
