/*
 * COM_LIN.c
 *
 *  Created on: 27 mai 2021
 *      Author: TheRolf
 */
#include "COM_LIN.h"

#include "cmsis_os.h"
#include "semphr.h"
#include "queue.h"

// on va chercher notre etat
extern uint8_t etat_commodo;

LINMSG etatMSG;
/**
 * @brief Cette fonction envoit un message contentant l'etat des commodos par LIN
 * @param reponse Si non nulle, le message n'enverra qu'une reponse, sinon il enverra un message
 */
void envoyer_etat_lin(uint8_t reponse) {
	etatMSG.length = 1;
	etat_commodo ^= 64;
	etatMSG.data[0] = etat_commodo;

	if(reponse) {
		SendResponse(&etatMSG);
	} else {
		etatMSG.ID = COMMODO_PID_EVENT;
		SendMessage(&etatMSG);
	}
}

extern osMessageQueueId_t linIDqueueHandle;
extern osSemaphoreId_t linBinarySemaphoreHandle;

/**
 * @brief cette fonction reçoit Ses callbacks du LIN afin de répondre à des requêtes de la part de l'actionneur
 * @param pid PID arrivant
 */
void callback_LIN(uint8_t pid) {
	uint8_t tmp_pid = pid;
	if(tmp_pid == COMMODO_PID_DEMANDE) {
		LINMSG demandeEtat;
		demandeEtat.ID = tmp_pid;
		demandeEtat.length = 0;

	    if (xPortIsInsideInterrupt()) {
	    	xQueueSendToBackFromISR(linIDqueueHandle,(void*) &demandeEtat, NULL);
	    }
	    else {
	    	xQueueSendToBack(linIDqueueHandle, (void*) &demandeEtat, 10);
	    }
	}
}
