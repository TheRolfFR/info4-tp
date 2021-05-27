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
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "usart2.h"
#include "COM_LIN.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
	CLIGNO_DROITE = 1,
	CLIGNO_REPOS = CLIGNO_DROITE * 2,
	CLIGNO_GAUCHE = CLIGNO_REPOS * 2,
} ClignoEtat;

typedef enum {
	FEUX_0 = CLIGNO_GAUCHE * 2,
	FEUX_AUTO = FEUX_0 * 2,
	FEUX_VEILLEUSES = FEUX_AUTO * 2,
	FEUX_ROUTE = FEUX_VEILLEUSES * 2
} FeuxEtat;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define ETAT_METTRE_BIT(variable, condition, value) do { if(condition) { variable |= value; } else { variable &= (~value); } } while(0)
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int data = 0;
uint8_t etat_commodo = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void process_frame(CAN_frame frame) {
	// ID déjà filtré
	// on va voir la DLC, le premier voire second bite
	if(frame.DLC >= 1) {
		// clignotants
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] & 0x4, CLIGNO_DROITE);
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] & 0x8, CLIGNO_REPOS);
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] & 0x10, CLIGNO_GAUCHE);
	}

	if (frame.DLC == 2) {
		// feux
		if((frame.Data[0] & 0x3) == 2) {
			ETAT_METTRE_BIT(etat_commodo, frame.Data[1] == 2 || frame.Data[1] == 5, FEUX_0);
			ETAT_METTRE_BIT(etat_commodo, frame.Data[1] == 3 || frame.Data[1] == 5, FEUX_AUTO);
			ETAT_METTRE_BIT(etat_commodo, frame.Data[1] == 4 || frame.Data[1] == 9, FEUX_VEILLEUSES);
			ETAT_METTRE_BIT(etat_commodo, frame.Data[1] == 0, FEUX_ROUTE);
		}
	}

	// bref quoi qu'il arrive on renvoie l'etat_commodo par LIN
	envoyer_etat_lin();
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	USART2_init_int(); // Init USART2 with 19200 bauds
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();

	/* USER CODE BEGIN 2 */

	// contruct big id
	uint32_t base = 0x10 << 24;
	uint32_t receiver = 0x51 << 16; // numéro de l'esclave: 51 c'est clignotants
	uint32_t emitter = 0x10 << 8; // numéro du poste
	uint32_t fonction = 0;

	uint32_t ext_id = base | receiver | emitter | fonction;
	uint16_t CAN_FilterIdHigh = ((ext_id << 3) >> 16) & 0xffff;
	uint16_t CAN_FilterIdLow = (uint16_t) (ext_id << 3) | CAN_ID_EXT;

	// on filtre uniquement la base et le receveur
	uint32_t ext_msk = 0xFFFF << 16;
	uint16_t CAN_FilterMskHigh = ((ext_msk << 3) >> 16) & 0xffff;
	uint16_t CAN_FilterMskLow = (uint16_t) (ext_msk << 3);

	CAN_config(0, CAN_FilterIdHigh, CAN_FilterIdLow, CAN_FilterMskHigh, CAN_FilterMskLow);

	UART_Init();
	LIN_SetSlave();
	LIN_SetReceiveCallback(callback_LIN);
	/* USER CODE END 2 */
	EXTI0_IRQHandler();
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief This function handles CAN1 RX0 interrupts.
 */
void CAN1_RX0_IRQHandler(void) {
	/* Light up LED and read CAN data*/

	uint8_t RxFifo = 0;

	/* Get header information into frame */
	CAN_frame frame;

	frame.IDE = CAN_ID_EXT; //(CAN_RI0R_IDE & CAN1->sFIFOMailBox[RxFifo].RIR);

	if (frame.IDE == CAN_ID_STD)
    {
    	frame.StdId = (CAN_RI0R_STID & CAN1->sFIFOMailBox[RxFifo].RIR) >> CAN_TI0R_STID_Pos;
    }
    else
    {
    	frame.ExtId = ((CAN_RI0R_EXID | CAN_RI0R_STID) & CAN1->sFIFOMailBox[RxFifo].RIR) >> CAN_RI0R_EXID_Pos;
    }
	frame.RTR = (CAN_RI0R_RTR & CAN1->sFIFOMailBox[RxFifo].RIR) >> CAN_RI0R_RTR_Pos;
	frame.DLC = (CAN_RDT0R_DLC & CAN1->sFIFOMailBox[RxFifo].RDTR) >> CAN_RDT0R_DLC_Pos;

    /* Get the data */
    frame.Data[0] = (uint8_t)((CAN_RDL0R_DATA0 & CAN1->sFIFOMailBox[RxFifo].RDLR) >> CAN_RDL0R_DATA0_Pos);
    frame.Data[1] = (uint8_t)((CAN_RDL0R_DATA1 & CAN1->sFIFOMailBox[RxFifo].RDLR) >> CAN_RDL0R_DATA1_Pos);
    frame.Data[2] = (uint8_t)((CAN_RDL0R_DATA2 & CAN1->sFIFOMailBox[RxFifo].RDLR) >> CAN_RDL0R_DATA2_Pos);
    frame.Data[3] = (uint8_t)((CAN_RDL0R_DATA3 & CAN1->sFIFOMailBox[RxFifo].RDLR) >> CAN_RDL0R_DATA3_Pos);
    frame.Data[4] = (uint8_t)((CAN_RDH0R_DATA4 & CAN1->sFIFOMailBox[RxFifo].RDHR) >> CAN_RDH0R_DATA4_Pos);
    frame.Data[5] = (uint8_t)((CAN_RDH0R_DATA5 & CAN1->sFIFOMailBox[RxFifo].RDHR) >> CAN_RDH0R_DATA5_Pos);
    frame.Data[6] = (uint8_t)((CAN_RDH0R_DATA6 & CAN1->sFIFOMailBox[RxFifo].RDHR) >> CAN_RDH0R_DATA6_Pos);
    frame.Data[7] = (uint8_t)((CAN_RDH0R_DATA7 & CAN1->sFIFOMailBox[RxFifo].RDHR) >> CAN_RDH0R_DATA7_Pos);

    /* Reset interrupt flag */
    CAN1->TSR |= CAN_TSR_RQCP0;
    CAN1->RF0R |= CAN_RF0R_RFOM0;
    CAN_printframe(frame);
	process_frame(frame);
}

/**
 * @brief This function handles USER button interrupts.
 */
void EXTI0_IRQHandler(void) {
	/* Clear interrupt flag */
	EXTI->PR = EXTI_PR_PR0;
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
}


/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* User button as input with pull up resistor */
	GPIOA->MODER &= ~GPIO_MODER_MODER0_Msk;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0_0;

	SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PA; // Enable interrupt on GPIOA
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->RTSR |= EXTI_RTSR_TR0; // Enable Rising Edge Trigger for PA0

	NVIC_SetPriority (EXTI0_IRQn, 1);  // Set Priority
	NVIC_EnableIRQ (EXTI0_IRQn);  // Enable Interrupt
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
