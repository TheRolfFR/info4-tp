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
	if((frame.ExtId & 0x3) == 0b10 && frame.DLC == 1) {
		// clignotants
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] & 0x4, CLIGNO_DROITE);
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] & 0x8, CLIGNO_REPOS);
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] & 0x10, CLIGNO_GAUCHE);
	}

	// feux
	// si c'est AN1 (0b01)
	if((frame.ExtId & 0x3) == 0b01 && frame.DLC == 1) {
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] == 0x80, FEUX_0); // 2.5V
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] == 0xB3, FEUX_AUTO); // 3.5V
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] == 0xFF, FEUX_VEILLEUSES); // 4.9 -> 5.0V
		ETAT_METTRE_BIT(etat_commodo, frame.Data[0] == 0x00, FEUX_ROUTE); // 0.0V
	}

	// bref quoi qu'il arrive on renvoie l'etat_commodo par LIN
	envoyer_etat_lin(0);
}
