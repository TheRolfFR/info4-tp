/*
 * acc.h
 *
 *  Created on: 21 mars 2021
 *      Author: achil
 */

#ifndef INC_ACC_H_
#define INC_ACC_H_

#include "stm32f4xx.h"

//Type def
typedef struct coord{
	int16_t x;
	int16_t y;
	int16_t z;
} coord;

//Define
#define HIGH 1
#define LOW 0

#define WHO_AM_I 0x0F

#define CTRL_REG6 0x25
#define CTRL_REG5 0x24
#define CTRL_REG4 0x20
#define CTRL_REG3 0x23
#define CTRL_REG2 0x22
#define CTRL_REG1 0x21

#define THRS2_1 0x56
#define THRS1_1 0x57
#define MASK1_B 0x59
#define MASK1_A 0x5A
#define SETT1 0x5B
#define OUTS1 0x5F

#define STx_1 0x40

#define OUT_X_LOW 0x28
#define OUT_Y_LOW 0x2A
#define OUT_Z_LOW 0x2C

#define WAI_DEF 0x3F

#define WR_MASK 0b01111111
#define RD_MASK 0b10000000

//Flags
extern uint8_t ACC_FLG;

//Macros
#define CS_SET GPIOE->ODR |= (0b1<<3)
#define CS_RESET GPIOE->ODR &= (0b0<<3)

//Functions
void ACC_GPIO_init();
void ACC_Setup(void);
coord ACC_get_coord(void);

void ACC_printData(struct coord * data);

#endif /* INC_ACC_H_ */
