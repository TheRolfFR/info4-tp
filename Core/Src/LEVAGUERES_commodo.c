/*
 * LEVAGUERES_commodo.C
 *
 *  Created on: 31 mai 2021
 *      Author: TheRolf
 */
#include "can.h"
#include "COM_LIN.h"
#include "LEVAGUERES_commodo.h"

#define ETAT_METTRE_BIT(variable, condition, value) do { if(condition) { variable |= value; } else { variable &= (~value); } } while(0)

void process_frame(CAN_frame frame) {
	// ID déjà filtré
	// on va voir les derniers bits voir si c'est le port A (0b10)
	if((frame.ExtId & 0xFF) == 0x10 && frame.DLC == 1) {
		// clignotants
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] & (1 << 2), CLIGNO_DROITE); // A2
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] & (1 << 3), CLIGNO_REPOS); // A3
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] & (1 << 4), CLIGNO_GAUCHE); // A4
	}

	// feux
	// si c'est AN1 (0b01)
	else if((frame.ExtId & 0xFF) == 0x01 && frame.DLC == 1) {
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] == 0x80, FEUX_0); // 2.5V
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] == 0xB3, FEUX_AUTO); // 3.5V
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] == 0xFF, FEUX_VEILLEUSES); // 4.9 -> 5.0V
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] == 0x00, FEUX_ROUTE); // 0.0V
	}

	// bref quoi qu'il arrive on renvoie l'etat_commodo par LIN
	envoyer_etat_lin(0);
}
