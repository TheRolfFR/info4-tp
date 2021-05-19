/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <queue.h>
#include <semphr.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TMP_BUFFER_LENGTH 200

#define A0 0
#define A1 0
#define A2 0
#define MCP_ADDRESS_READ ((0b0011 << 4 | (A2 << 3) | (A1 << 2) | (A0 << 1)) & 0xFE)
#define MCP_ADDRESS_WRITE (MCP_ADDRESS_READ | 0x01)

#define MCP_REG_WHOAMI 0x07
#define MCP_REG_TEMP 0x05
#define MCP_REG_RES 0x08
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* Definitions for tempTask */
osThreadId_t tempTaskHandle;
const osThreadAttr_t tempTask_attributes = {
  .name = "tempTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
volatile QueueHandle_t queueTemp = NULL;
char tmp_buffer[TMP_BUFFER_LENGTH];
SemaphoreHandle_t temp_semaphore;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
void tempTaskStart(void *argument);

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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  queueTemp = xQueueCreate(5, sizeof(uint16_t));
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of tempTask */
  tempTaskHandle = osThreadNew(tempTaskStart, NULL, &tempTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  HAL_UART_Transmit(&huart2, (uint8_t*) "Start of scheduler\r\n", strlen("Start of scheduler\r\n"), configTICK_RATE_HZ / 2);
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if(hi2c->Instance == I2C1) {
		if(hi2c->Devaddress == MCP_ADDRESS_WRITE) {
			BaseType_t morePriorTask;
			xSemaphoreGiveFromISR(temp_semaphore, &morePriorTask);

			portYIELD_FROM_ISR(morePriorTask);
		}
	}
}

void HAL_I2C_MasterRxCpltCallback (I2C_HandleTypeDef * hi2c)
{
	if(hi2c->Instance == I2C1) {
		if(hi2c->Devaddress == MCP_ADDRESS_READ) {
			BaseType_t morePriorTask;
			xSemaphoreGiveFromISR(temp_semaphore, &morePriorTask);

			portYIELD_FROM_ISR(morePriorTask);
		}
	}
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_tempTaskStart */
/**
  * @brief  Function implementing the tempTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_tempTaskStart */
void tempTaskStart(void *argument)
{
  /* USER CODE BEGIN 5 */

	// create sem
	temp_semaphore = xSemaphoreCreateBinary();

	// final value
	float temp;
	uint8_t UpperByte, LowerByte;
	uint8_t registerToRead;

	// WHOAMI
	registerToRead = MCP_REG_WHOAMI; // registre whoami
	uint8_t device_id_and_rev[2]; // destination

	// lecture du registre de deux octets
	HAL_I2C_Master_Transmit_IT(&hi2c1, MCP_ADDRESS_WRITE, &registerToRead, 1);
	xQueueSemaphoreTake(temp_semaphore, portMAX_DELAY);
	HAL_I2C_Master_Receive_IT(&hi2c1, MCP_ADDRESS_READ, device_id_and_rev, 2);
	xQueueSemaphoreTake(temp_semaphore, portMAX_DELAY);

	// on vérifie bon id
	if(device_id_and_rev[0] == 0x04) {
		snprintf(tmp_buffer, TMP_BUFFER_LENGTH, "Good device ID %d REV %d\r\n", (int) device_id_and_rev[0], (int) device_id_and_rev[1]);
		HAL_UART_Transmit(&huart2, (uint8_t*) tmp_buffer, strlen(tmp_buffer), configTICK_RATE_HZ/2);
	} else {
		snprintf(tmp_buffer, TMP_BUFFER_LENGTH, "Incorrect device ID %d\r\n", (int) device_id_and_rev[0]);
		HAL_UART_Transmit(&huart2, (uint8_t*) tmp_buffer, strlen(tmp_buffer), configTICK_RATE_HZ/2);
	}

	// changement de la resolution
	registerToRead = MCP_REG_RES;
	// ------XX
	// 00 : +0.5°C (tconv = 30ms)
	// 01 : +0.25°C (tconv = 65ms)
	// 10 : +0.125°C (tconv = 130ms)
	// 11 : +0.0625°C (tconv = 250ms) (valeur par défaut power-up)
	uint8_t reg_and_res[2] = { MCP_REG_RES, 0b11 }; // resolution max
	HAL_I2C_Master_Transmit_IT(&hi2c1, MCP_ADDRESS_WRITE, reg_and_res, 2);
	xQueueSemaphoreTake(temp_semaphore, portMAX_DELAY);

	/* Infinite loop */
	uint8_t temp_response[2];
	registerToRead = MCP_REG_TEMP; // registre de temp
	for(;;)
	{
		// lecture regitre température 2 octets
		HAL_I2C_Master_Transmit_IT(&hi2c1, MCP_ADDRESS_WRITE, &registerToRead, 1);
		xQueueSemaphoreTake(temp_semaphore, portMAX_DELAY);
		HAL_I2C_Master_Receive_IT(&hi2c1, MCP_ADDRESS_READ,temp_response, 2);
		xQueueSemaphoreTake(temp_semaphore, portMAX_DELAY);

		// sépare upper et lower byte
		UpperByte = temp_response[0];
		LowerByte = temp_response[1];

		// on clear les flags
		UpperByte &= 0x1F;

		// on calcule selon le signe
		if((UpperByte & 0x10) == 0x10) {
			temp = 256 - (UpperByte * 16.f + LowerByte / 16.f);
		} else {
			temp = UpperByte * 16.f + LowerByte / 16.f;
		}

		snprintf(tmp_buffer, TMP_BUFFER_LENGTH, "\r%f°C ", temp);

		HAL_UART_Transmit(&huart2, (uint8_t*) tmp_buffer, strlen(tmp_buffer), configTICK_RATE_HZ/2);

		osDelay(configTICK_RATE_HZ/4); // attends Tconv=250ms
	}
  /* USER CODE END 5 */
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
