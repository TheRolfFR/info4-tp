/*
 * COM_LIN.h
 *
 *  Created on: 27 mai 2021
 *      Author: TheRolf
 */
#include "UART_LIN.h"

/**
 * @brief Cette fonctoion envoi un message contentant l'etat des commodos par LIN
 */
void envoyer_etat_lin();

/**
 * @brief cette fonction reçoit les callbacks du LIN afin de répondre à des requêtes de la part de l'actionneur
 * @param pid PID arrivant
 */
void callback_LIN(uint8_t pid);
