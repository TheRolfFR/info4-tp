/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Nicolas Lacaille
 * @brief          : Main program body
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define STACK_SIZE	512 // in words (= 4*STACK_SIZE bytes)

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
volatile SemaphoreHandle_t semaphoreBinairePulse;

/* Private function prototypes -----------------------------------------------*/
void pin_init(void);
void T0( void * pvParameters );
void T1( void * pvParameters );
void T2( void * pvParameters );

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	BaseType_t xReturned0;
	(void) xReturned0;
	TaskHandle_t xHandle0 = 0;

	/*priority grouping 4 bits for preempt priority 0 bits for subpriority
	 * (No Subpriority) for FreeRTOS*/
	NVIC_SetPriorityGrouping( 3 );

	/*
	 * Peripheral init
	 */
	/* USART2 */
	USART2_Init(115200);

	/* tasks creation :
	 * priority are from 0 (tskIDLE_PRIORITY) to configMAX_PRIORITIES
	 * in FreeRTOSConfig.h
	 */

	// première tache pour faire clignoter la led
    xReturned0 = xTaskCreate(
                    T0,       /* Function that implements the task. */
                    "Clignoter led",          /* Text name for the task. */
                    STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY+7,/* Priority at which the task is created. */
                    &xHandle0 );      /* Used to pass out the created task's handle. */

    // On crée notre sémaphore
    semaphoreBinairePulse = xSemaphoreCreateBinary();

    printf("Démarrage du scheduler \n");
    // start the scheduler, tasks will be started and the
    // function will not return
	vTaskStartScheduler();

	//* never go there if scheduler has started */
	/* Loop forever */
	for(;;);
}

void configCapture() {
	// le USER BUTTON est en pull up
	// donc quand pressé fait haut->bas->haut

    // activer gpio B
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // PB7 alternate function (2) : AF02 TIM4 channel 2 (2)
	GPIOB->MODER &= ~GPIO_MODER_MODER7_Msk;
	GPIOB->MODER |= GPIO_MODER_MODER7_1;
	GPIOB->AFR[0] &= ~GPIO_AFRH_AFRH7; // 0
	GPIOB->AFR[0] |=  GPIO_AFRH_AFRH7_1; // 2

    // activer timer 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	// Mettre la vitesse du Timer 4
	// TIM4  bits: max(ARR) = 2^16 - 1
	TIM4->PSC = 0; // prescaler to 1
	TIM4->ARR = 0xFFFF;

	// activer les modifications CCMR2
	TIM4->CCER &= ~TIM_CCER_CC1E;
	TIM4->CCER &= ~TIM_CCER_CC2E;

	// Mettre filtre IC2 : 0b10
	TIM4->CCMR1 &= ~TIM_CCMR1_IC2F_Msk;
	TIM4->CCMR1 |= 0b0010 << TIM_CCMR1_IC2F_Pos; // N=4 pour downcounter

	// Mettre le prescaler d'évènement : détecter un changement sur chaque front
	// capture is done each time an edge is detected on the capture input
	TIM4->CCMR1 &= ~TIM_CCMR1_IC1PSC;
	TIM4->CCMR1 &= ~TIM_CCMR1_IC2PSC;

	// rediriger CC1 channel vers TI2 (valeur 2)
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_Msk;
	TIM4->CCMR1 |= 2 << TIM_CCMR1_CC1S_Pos;

	// rediriger CC2 channel vers TI2 (valeur 1)
	TIM4->CCMR1 &= ~TIM_CCMR1_CC2S_Msk;
	TIM4->CCMR1 |= 1 << TIM_CCMR1_CC2S_Pos;

	// mettre la détection de front
	TIM4->CCER &= ~(TIM_CCER_CC1NP_Msk | TIM_CCER_CC1P_Msk);
	TIM4->CCER &= ~(TIM_CCER_CC2NP_Msk | TIM_CCER_CC2P_Msk);

	// front montant, signal TI2FP1, qui sera lui aiguillé sur le signal IC1 : noninverted/riging edge : (0/0) CCR1
	// front descendant, signal TI2FP2, qui sera aiguillé sur le signal IC2 : inverted/falling edge : (0/1) CCR2
	TIM4->CCER |= TIM_CCER_CC2P;

	// activer la capture CC1 et CC2
	TIM4->CCER |= TIM_CCER_CC1E;
	TIM4->CCER |= TIM_CCER_CC2E;

	// activer le compteur 1
	TIM4->CR1 |= TIM_CR1_CEN;

	// trigger force 0
    TIM4->EGR |= TIM_EGR_UG;

    // activer les interruptions pour le timer 4
	NVIC_SetPriority(TIM4_IRQn, 6);
	NVIC_EnableIRQ(TIM4_IRQn);

	// activer les interruptions pour le overflow, le cc1 et cc2 plus tard
	TIM4->DIER |= TIM_DIER_CC2IE | TIM_DIER_UIE | TIM_DIER_CC1IE;
}

uint32_t overflow = 0;
uint16_t ccr1, ccr2;

/**
 * @brief Fonction bloquante qui donne la durée de la pulse
 * @param[out] diff_ms Pointeur où envoyer la valeur de la différence en ms
 * @param[out] ovr_ms Pointeur où envoyer la valeur de la différence en overflow en ms
 */
void get_pulse(uint32_t *diff_ms, uint32_t *ovr_ms) {

	xSemaphoreTake(semaphoreBinairePulse, portMAX_DELAY);

	uint32_t timespan;
	if(ccr1 > ccr2) {
		timespan = ccr1 - ccr2;
	} else {
		overflow--;
		timespan = (ccr1 + TIM4->ARR + 1) - ccr2;
	}

	// pour faire court, un overflow dure (ARR+1) / (SystemCoreClock / (PSC + 1)) secondes (car on est en Hertz)

	// ne pas changer le calcul optimisé
	*ovr_ms = overflow * (TIM4->ARR + 1) / (SystemCoreClock / (TIM4->PSC + 1) / 1000);
	*diff_ms = timespan / (SystemCoreClock / (TIM4->PSC + 1) / 1000);
}

void TIM4_IRQHandler() {

	if((TIM4->DIER & TIM_DIER_UIE) && (TIM4->SR & TIM_SR_UIF)) {
		++overflow;

		TIM4->SR &= ~TIM_SR_UIF;
	}

	if((TIM4->DIER & TIM_DIER_CC2IE) && (TIM4->SR & TIM_SR_CC1IF))  {
		// CCR1 est montant donc fin
		ccr1 = TIM4->CCR1;

		// activer les interruptions pour overflow and rising
		BaseType_t tacheDebloquee; // mise à pdTrue si tache plus prioritaire débloquée
		xSemaphoreGiveFromISR(semaphoreBinairePulse, &tacheDebloquee);

		// clear CC1IF interrupt flag
		TIM4->SR &= ~TIM_SR_CC1IF;

		portYIELD_FROM_ISR(tacheDebloquee);
	}

	if((TIM4->DIER & TIM_DIER_CC1IE) && (TIM4->SR & TIM_SR_CC2IF)) {
		// CC2IF est descendant donc début

		// restart the overflow counter
		overflow = 0;

		// get the ccr2 value
		ccr2 = TIM4->CCR2;


		// clear CC1IF interrupt flag
		TIM4->SR &= ~TIM_SR_CC2IF;
	}
}

/**
 * @brief	Task TO
 * @param	parameters given @ creation
 * @retval	none (should not return)
 */
void T0( void * pvParameters ) {
	configCapture();

	uint32_t diff_ms, overflow_ms;

	for(;;) {
		get_pulse(&diff_ms, &overflow_ms);
		(void) diff_ms;
		(void) overflow_ms;
		__NOP();
	}
}

//#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1){

  }
}
//#endif
