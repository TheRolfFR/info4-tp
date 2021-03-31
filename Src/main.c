/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Claussspe license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include <stdint.h>
#include <string.h>
#include <stm32f4xx.h>
#include "usart.h"

extern uint32_t SystemCoreClock;

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void init_pwm() {

	// 4 étapes par (1/2) => 0.5s => 500ms
	// la duree totale de 0% à 100% sera : etapes * numerateur / denominateur en secondes

	// ATTENTION METTRE LES NOMBRES LES PLUS PETITS SINON OVERFLOW
	uint16_t numerateur = 1;
	uint16_t denominateur = 2;

	// activer GPIO A
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// clear mode PA5
	GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;

	// PA5 alternate function (2) : AF01 TIM2 channel 1 (1)
	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	GPIOA->AFR[0] &= ~GPIO_AFRH_AFRH5; // 0
	GPIOA->AFR[0] |=  GPIO_AFRH_AFRH5_0; // 1

	// activer timer 5
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

	// on peut mettre le prescaler à 1 car notre valeur rentrera dans 32 bits
	TIM5->PSC = 0;

	// IMPORTANT NE PAS METTRE DE PARENTHESES SUR LE QUOTIENT SINON 0
	// TIM5 32 bits: max(ARR) = 2^32 - 1
	TIM5->ARR = SystemCoreClock*numerateur/denominateur-1;

	// activer timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// 10kHz
	// TIM2 32 bits: max(ARR) = 2^32 - 1
	uint16_t prescaler = 1;
	uint16_t freq = 10000;
	uint32_t autoreload = SystemCoreClock / (prescaler * freq);
	TIM2->PSC = prescaler - 1;
	TIM2->ARR = autoreload - 1;


	// Mettre en mode PWM1
	TIM2->CCMR1 &= ~TIM_CCMR1_CC1S; // Le mode output compare est 0
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M; // clear output mode
	TIM2->CCMR1 |=  110 << TIM_CCMR1_OC1M_Pos; // Mettre le mode output en PWM1
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1CE;

	// activer sortie
	TIM2->CCER &= ~TIM_CCER_CC1E;
	TIM2->CCER |=  TIM_CCER_CC1E;

	// premiere intensité lumineuse 0%
	TIM2->CCR1 = 0;

	// on oublie pas de activer les compteurs
	TIM2->CR1 |= TIM_CR1_CEN;
	TIM5->CR1 |= TIM_CR1_CEN;

	// on génère un évènement de reset de compteur
	TIM5->EGR |= TIM_EGR_UG;
}

void init_capture() {
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
	TIM4->PSC = 16-1; // prescaler to 16
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
}

void ex2_big_loop() {

	// variables pwm
	uint16_t etapes = 4;
	uint16_t compteur = 0;
	uint8_t croissant = 0; // croissant premiere fois

	// variables capture
    uint32_t timespan;
    uint32_t time_overflow_ms;
    (void) time_overflow_ms;
	uint32_t time_diff_ms;
    (void) time_diff_ms;
    uint32_t overflow = 0;
    uint16_t ccr1, ccr2;


    uint32_t bufferSize = 200;
    uint8_t buffer[200];
    memset(buffer, 0, 200);

    char logBuffer[500];
    USART2_BigLoop_Receive(buffer, bufferSize);

	while(1) {
		// PWM update
		if(TIM5->SR & TIM_SR_UIF) { // a chaque update
			if(compteur % etapes == 0) {
				croissant = !croissant;
			}

			if(croissant)
				++compteur;
			else
				--compteur;

			TIM2->CCR1 = compteur * TIM2->ARR / etapes;

			// on clear l'interrupt flag d'update
			TIM5->SR = TIM5->SR & (~TIM_SR_UIF);
		}

		// capture
    	if(TIM4->SR & TIM_SR_UIF) {
    		++overflow;
    		if(overflow == UINT32_MAX) {
    			__NOP();
    		}

    		TIM4->SR &= ~TIM_SR_UIF;
		}

    	if((TIM4->SR & TIM_SR_CC1IF))  {
    		// CCR1 est montant donc fin
    		ccr1 = TIM4->CCR1;


    		if(ccr1 > ccr2) {
    			timespan = ccr1 - ccr2;
    		} else {
    			overflow--;
    			timespan = (ccr1 + TIM4->ARR + 1) - ccr2;
    		}

    		// pour faire court, un overflow dure (ARR+1) / (SystemCoreClock / (PSC + 1)) secondes (car on est en Hertz)

    		// ne pas changer le calcul optimisé
    		//in ms : (pulse*tim->PSC)/(SystemCoreClock/1000); // (pulse*1000/frequ)
    		time_overflow_ms = (overflow) / (SystemCoreClock / (TIM4->PSC+1) / 1000);
    		time_diff_ms = (timespan) / (SystemCoreClock / (TIM4->PSC+1) / 1000);

    	    memset(logBuffer, 0, 500);
    	    strcat(logBuffer, "Nouveau log duree:\r\n");
    	    sprintf(logBuffer+strlen(logBuffer), "Valeur overflow: %hu\r\n", overflow);
    	    sprintf(logBuffer+strlen(logBuffer), "Valeur timespan: %hu\r\n", timespan);
    	    sprintf(logBuffer+strlen(logBuffer), "Duree overflow ms: %hu\r\n", time_overflow_ms);
    	    sprintf(logBuffer+strlen(logBuffer), "Duree time ms: %hu\r\n", time_diff_ms);
    	    USART2_BigLoop_Transmit((uint8_t*) logBuffer, strlen(logBuffer)+1);

			// clear CC1IF interrupt flag
			TIM4->SR &= ~TIM_SR_CC1IF;
    	}

    	if((TIM4->SR & TIM_SR_CC2IF)) {
    		// CC2IF est ddescendant donc début

    		// restart the overflow counter
			overflow = 0;

			// get the ccr2 value
    		ccr2 = TIM4->CCR2;


			// clear CC1IF interrupt flag
			TIM4->SR &= ~TIM_SR_CC2IF;
		}

    	//usart
    	USART2_BigLoop_ReceiveBuffer();
    	USART2_BigLoop_TransmitBuffer();
	}
}

int main(void)
{
	init_pwm();
	init_capture();
	USART2_Init(115200);

	ex2_big_loop();
}
