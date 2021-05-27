/*
 * COM_LIN.c
 *
 *  Created on: 27 mai 2021
 *      Author: TheRolf
 */
#include "COM_LIN.h"

#define COMMODO_PID 0xC0

// on va chercher notre etat
extern uint8_t etat_commodo;

/**
 * @brief Cette fonctoion envoi un message contentant l'etat des commodos par LIN
 */
LINMSG etatMSG;
void envoyer_etat_lin()  {
	etatMSG.ID = COMMODO_PID;
	etatMSG.length = 1;
	etatMSG.data[0] = etat_commodo;
}

/**
 * @brief cette fonction reçoit les callbacks du LIN afin de répondre à des requêtes de la part de l'actionneur
 * @param pid PID arrivant
 */
void callback_LIN(uint8_t pid) {
	if(pid == COMMODO_PID) {
		envoyer_etat_lin();
	}
}
