/*
 * COM_LIN.h
 *
 *  Created on: 27 mai 2021
 *      Author: TheRolf
 */
#include "UART_LIN.h"

/**
 * @brief Cette fonction envoit un message contentant l'etat des commodos par LIN
 * @param reponse Si non nulle, le message n'enverra qu'une reponse, sinon il enverra un message
 */
void envoyer_etat_lin(uint8_t reponse);

/**
 * @brief cette fonction reçoit les callbacks du LIN afin de répondre à des requêtes de la part de l'actionneur
 * @param pid PID arrivant
 */
void callback_LIN(uint8_t pid);
