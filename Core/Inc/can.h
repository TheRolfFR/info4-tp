/*
 * can.h
 *
 *  Created on: Mar 29, 2021
 *      Author: Ryan HADJ MEBAREK
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

#include "stm32f4xx_hal.h"

typedef struct CAN_frame CAN_frame;
struct CAN_frame
{
    uint32_t StdId;
    uint32_t ExtId;
    uint8_t IDE;
    uint8_t RTR;
    uint8_t DLC;
    uint8_t Data[8];
};

void CAN_config(uint8_t IDE, uint16_t Filter_ID_high, uint16_t Filter_ID_low, uint16_t Filter_Mask_high, uint16_t Filter_mask_low);
uint8_t CAN_envoi(CAN_frame CAN_mes);
void CAN_printframe(CAN_frame fr);

#endif /* INC_CAN_H_ */
