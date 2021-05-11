/*
 * rtc.c
 *
 *  Created on: Mar 21, 2021
 *      Author: /
 */


#include "rtc.h"

void RTC_getValue(char *buffer, char *buffer_jour) {
	int Hours, Minutes, Seconds;
	int Date, Month, Year, WeekDay;

	//Acquisition heure et date
	Hours = RTC->TR >> 16U;
	Minutes = (RTC->TR >> 8U) & 0x00FF;
	Seconds = RTC->TR & 0x0000FF;

	Year = RTC->DR >> 16U;
	Month = (RTC->DR >> 8U) & 0x001F;
	Date = (RTC->DR) & 0x00003F;
	WeekDay = (RTC->DR >> 13U) & 0x7;

	//Convertion code jour en charactere
	switch (WeekDay) {
	case 1:
		buffer_jour[0] = 'L';
		buffer_jour[1] = 'U';
		buffer_jour[2] = 'N';
		buffer_jour[3] = 'D';
		buffer_jour[4] = 'I';
		break;
	case 2:
		buffer_jour[0] = 'M';
		buffer_jour[1] = 'A';
		buffer_jour[2] = 'R';
		buffer_jour[3] = 'D';
		buffer_jour[4] = 'I';
		break;
	case 3:
		buffer_jour[0] = 'M';
		buffer_jour[1] = 'E';
		buffer_jour[2] = 'R';
		buffer_jour[3] = 'C';
		buffer_jour[4] = 'R';
		buffer_jour[5] = 'E';
		buffer_jour[6] = 'D';
		buffer_jour[7] = 'I';
		break;
	case 4:
		buffer_jour[0] = 'J';
		buffer_jour[1] = 'E';
		buffer_jour[2] = 'U';
		buffer_jour[3] = 'D';
		buffer_jour[4] = 'I';
		break;
	case 5:
		buffer_jour[0] = 'V';
		buffer_jour[1] = 'E';
		buffer_jour[2] = 'N';
		buffer_jour[3] = 'D';
		buffer_jour[4] = 'R';
		buffer_jour[5] = 'E';
		buffer_jour[6] = 'D';
		buffer_jour[7] = 'I';
		break;
	case 6:
		buffer_jour[0] = 'S';
		buffer_jour[1] = 'A';
		buffer_jour[2] = 'M';
		buffer_jour[3] = 'E';
		buffer_jour[4] = 'D';
		buffer_jour[5] = 'I';
		break;
	case 7:
		buffer_jour[0] = 'D';
		buffer_jour[1] = 'I';
		buffer_jour[2] = 'M';
		buffer_jour[3] = 'A';
		buffer_jour[4] = 'N';
		buffer_jour[5] = 'C';
		buffer_jour[6] = 'H';
		buffer_jour[7] = 'E';
		break;
	default:

		break;
	}

	//Convertion hexa en charactere
	buffer[0] = (Date / 16) + 48;
	buffer[1] = (Date % 16) + 48;
	buffer[2] = '.';
	buffer[3] = (Month / 16) + 48;
	buffer[4] = (Month % 16) + 48;
	buffer[5] = '.';
	buffer[6] = '2';
	buffer[7] = '0';
	buffer[8] = (Year / 16) + 48;
	buffer[9] = (Year % 16) + 48;
	buffer[10] = '@';
	buffer[11] = (Hours / 16) + 48;
	buffer[12] = (Hours % 16) + 48;
	buffer[13] = ':';
	buffer[14] = (Minutes / 16) + 48;
	buffer[15] = (Minutes % 16) + 48;
	buffer[16] = ':';
	buffer[17] = (Seconds / 16) + 48;
	buffer[18] = (Seconds % 16) + 48;

}

void RTC_printDate(char *buffer, char *buffer_jour) {
	RTC_UsartTransmit((uint8_t*)buffer_jour, (int) strlen(buffer_jour));

	USART2_putc(' ');

	RTC_UsartTransmit((uint8_t*)buffer, (int) strlen(buffer));

	USART2_putc('\n');
	USART2_putc('\r');
}


void RTC_UsartTransmit(uint8_t *data, int len) {
	for (int i = 0; i < len; ++i) {
		USART2_putc(data[i]);
	}
}

void RTC_Init(void) {

	// Active l'horloge RTC
	__HAL_RCC_RTC_ENABLE();

	// Desactive la protection en ecriture
	RTC->WPR = 0xCAU;
	RTC->WPR = 0x53U;

	// Mode init
	RTC->ISR = (uint32_t) 0xFFFFFFFFU;

	// Attente flag init
	while (!(RTC->ISR & 0x1UL << 6))
		;

	// Configuration prescaler
	RTC->PRER = 0xFFU;
	RTC->PRER |= 0x7FU << 16;

	// Configuration heures, minutes, secondes
	RTC->TR = 0x17U << 16 | 0x45U << 8 | 0x00U;

	// Configuration annee, mois, jour, jour de la semaine
	RTC->DR = 0x21U << 16 | 0x03U << 8 | 0x22U | 0x01U << 13;

	// Fin mode init
	RTC->ISR &= (uint32_t) ~RTC_ISR_INIT;

	// Active la protection en ecriture
	RTC->WPR = 0xFFU;
}

