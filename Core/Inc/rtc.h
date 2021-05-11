/*
 * rtc.h
 *
 *  Created on: Mar 21, 2021
 *      Author: /
 */

#ifndef INC_RTC_RTC_H_
#define INC_RTC_RTC_H_

#include "stm32f4xx_hal.h"
#include "usart2.h"
#include <string.h>
#include <time.h>

void RTC_Init();
void RTC_getValue(char *buffer, char *buffer_jour);
void RTC_printDate(char *buffer, char *buffer_jour);
void RTC_UsartTransmit(uint8_t *data, int len);


#endif /* INC_RTC_RTC_H_ */
