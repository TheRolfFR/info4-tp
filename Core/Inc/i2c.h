/*
 * i2c.h
 *
 *  Created on: 10 f�vr. 2020
 *      Author: aravey
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx_hal.h"

//Prototype
void init_I2C1(void);
void I2C_Master_Transmit(uint8_t addr, uint8_t *buffer, uint8_t size);
void I2C_Master_Receive(uint8_t addr, uint8_t *buffer, uint8_t size);
void I2C_Slave_Receive(uint8_t *buffer, uint8_t size);

#endif /* I2C_H_ */
