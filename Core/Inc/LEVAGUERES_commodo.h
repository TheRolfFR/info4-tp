/*
 * LEVAGUERES_commodo.h
 *
 *  Created on: 31 mai 2021
 *      Author: TheRolf
 */

#ifndef INC_LEVAGUERES_COMMODO_H_
#define INC_LEVAGUERES_COMMODO_H_

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

uint8_t etat_commodo;

void process_frame(CAN_frame frame);

#endif /* INC_LEVAGUERES_COMMODO_H_ */
