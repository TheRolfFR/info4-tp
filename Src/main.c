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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stm32f4xx.h>
#include "system.h"
#include <string.h>
#include "usart.h"

// Définitions activation exercices
#define ACTIVER_AUTRES_TACHES  1
#define ACTIVER_YIELD_CRITIQUE 1
#define UNE_SEULE_TACHE (!defined(ACTIVER_AUTRES_TACHES) || ACTIVER_AUTRES_TACHES == 0)
#define YIELD_CRITIQUE defined(ACTIVER_YIELD_CRITIQUE) && ACTIVER_YIELD_CRITIQUE == 1

// Définitions GPIOs et broches
#define GPIO_LED GPIOA
#define GPIO_PIN_LED 5
#define GPIO_BOUTON GPIOC
#define GPIO_PIN_BOUTON 13

// variable externes
extern uint32_t scheduler;
extern uint32_t SystemCoreClock;
extern volatile struct TCB_t * current_tcb;

// Définitions de nos taches
#define STACK_SIZE 500
// Structure custom pour les taches
typedef struct _task {
	uint32_t stack[STACK_SIZE]; // notre stack
	volatile TCB tcb; // notre TCB
} Task_t;

// Indices pour les champs de la stack frame
#define INDEX_EXEC_RETURN 0
#define INDEX_CONTROL 1
#define INDEX_RETURNADDR 16
#define INDEX_XPSR 17

// volatiles pour éviter les optimisations en mémoire
volatile Task_t tasks[3];
volatile void* functions[3];

/**
 * @brief initialise la task avec le TCB suivant et la fonction de démarrage
 * @param[in] t La structure tache à initialiser
 * @param next Le TCB suivant
 * @param fun Adresse de la fonction à lancer au démarrage
 */
void task_init(volatile Task_t *t, volatile TCB* next, volatile void* fun) {
	// on fait le plus facile on lie le suivant et on pose le stack
	t->tcb.next = next;
	t->tcb.stack = &(t->stack[STACK_SIZE - 18]);

	// exec return mode : Thread = 0xFFFFFFFD donc pile PSP
	t->tcb.stack[INDEX_EXEC_RETURN] = 0xFFFFFFFD;

	// CONTROL : mode d'ouverture 2=privilégié, 3=non priviligié
	t->tcb.stack[INDEX_CONTROL] = (uint32_t) 2;

	// specific xpsr value
	t->tcb.stack[INDEX_XPSR] = 0x01000000;

	memset((uint8_t*) &(t->tcb.stack[2]), 0, 14*sizeof(uint32_t));

	// on met la fonction ici
	t->tcb.stack[INDEX_RETURNADDR] = (uint32_t) fun;
}

void task_yield() {
#if YIELD_CRITIQUE
	SVC(TASK_YIELD);
#endif
}

#if YIELD_CRITIQUE
uint32_t critical = 0;
#endif
void enter_critical() {
#if YIELD_CRITIQUE
	scheduler = 0;
	__disable_irq();
	++critical;
#endif
}

void exit_critical() {
#if YIELD_CRITIQUE
	if(--critical == 0) {
		__enable_irq();
		scheduler = 1;
	}
#endif
}

void blink_init() {
	// on active le GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// PA5 sortie : MODER = 01
	GPIO_LED->MODER &= ~(0b11 << (GPIO_PIN_LED * 2));
	GPIO_LED->MODER |= (0b1 << (GPIO_PIN_LED * 2));
}

uint32_t max1 = 100000;
uint32_t max2 = 300000;
uint32_t max  = 100000;

// Tache de la LED
void blink_loop() {
	uint32_t counter;

	while(1) {
		counter = 0;
		while(counter < max) {
			++counter;
		}

		uint8_t newLedState = ! (GPIO_LED->ODR & (1 << GPIO_PIN_LED));
		GPIO_LED->ODR &= (~(1 << GPIO_PIN_LED));
		GPIO_LED->ODR |= (newLedState << GPIO_PIN_LED);

		task_yield();
	}
}

// Fonction d'initialisation de bouton
void button_init() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// PC13 entrée
	GPIO_TypeDef* gpioc = GPIO_BOUTON;
	gpioc->MODER &= ~(0b11 << (GPIO_PIN_BOUTON * 2)); // in : 00
}

// Tache du bouton
void button_loop() {
	// délai entre chaque bouton pressé
	uint32_t debounce = 250000;

	// je démarre le debounce counter avec la valeur
	// de debounce pour faire marcher le bouton tout de suite
	uint32_t decounceCounter = debounce;

	while(1) {
		// je mets un compteur de debounce pour
		// mettre un delai pendant les appuis
		while(decounceCounter < debounce) {
			++decounceCounter;
		}

		// si le bouton est appuyé (user button en pullup) (= 0)
		if((GPIO_BOUTON->IDR & (1 << GPIO_PIN_BOUTON)) == 0) {
			max = (max == max1) ? max2 : max1;

			char chaine[] = "Bouton appuyé\r\n";
			enter_critical();
			USART2_Transmit((uint8_t*) chaine, strlen(chaine) + 1);
			exit_critical();

			decounceCounter = 0;
		}

		// je suis généreux
		// je lache la main pour le suivant
		task_yield();
	}
}

// Fonction d'initialisation de périphérique pour la tache usart
void usart_init() {
	USART2_Init(115200);
}

// Tache usart
void usart_loop() {
	// compteur de délai
	uint32_t counter;

	// indice du heartbeat
	uint32_t messageIndex = 0;

	// forme du message à envoyer
	char prefix[] = "Heartbeat ";
	char* messageIndexChar = NULL;
	char suffix[] = " : Je suis vivant !\r\n";

	while(1) {
		// délai d'attente entre les messages
		counter = 0;
		while(counter < max2) {
			++counter;
		}

		// je transmet mon heartbeat
		USART2_Transmit((uint8_t*) prefix, strlen(prefix));
		messageIndexChar = uint2str(messageIndex++);
		USART2_Transmit((uint8_t*) messageIndexChar, strlen(messageIndexChar) + 1);
		USART2_Transmit((uint8_t*) suffix, strlen(suffix));

		// je suis généreux
		// je lache la main pour le suivant
		task_yield();
	}
}

int main(void)
{
	// j'initialise tous mes périphériques et broches
	// avant de lancer mes taches
	blink_init();
	button_init();
	usart_init();

	// je met mes fonctions dans un tableau pour écrire le round robin plus facilement
	functions[0] = blink_loop;
#if !UNE_SEULE_TACHE
	functions[1] = button_loop;
	functions[2] = usart_loop;
#endif

#if UNE_SEULE_TACHE
	task_init(task[0], &(tasks[0].tcb), functions[0])
#else
	// j'initiaise toutes les structures tache
	for(uint8_t i = 0; i < 3; ++i) {
		task_init(&(tasks[i]), &(tasks[(i+1)%3].tcb), functions[i]);
	}
#endif

	// je prend le premier tcb pour le current tcb
	current_tcb = &(tasks[0].tcb);

	// On met les priorité et on active pendingSV
	NVIC_SetPriority (PendSV_IRQn, 15);
	NVIC_EnableIRQ (PendSV_IRQn);

	// on démarre la clock avec déclenchement de 10ms
	SysTick_Config(SystemCoreClock / 10000);

	// on lance la première tache et on active le scheduler
	SVC(0);

	// on ne devrait jamais venir ici normalement
	while(1) {
		__NOP();
	}
}
