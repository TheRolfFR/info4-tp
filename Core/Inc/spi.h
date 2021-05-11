/*
 * spi.h
 *
 *  Created on: 18 f�vr. 2020
 *      Author: aravey
 */

#ifndef SPI_H_
#define SPI_H_



#endif /* SPI_H_ */
#include "stm32f4xx_hal.h"

//defines
#define CS_Pin GPIO_PIN_3
#define CS_GPIO_Port GPIOE
#define SCK_Pin GPIO_PIN_5
#define SCK_GPIO_Port GPIOA
#define MISO_Pin GPIO_PIN_6
#define MISO_GPIO_Port GPIOA
#define MOSI_Pin GPIO_PIN_7
#define MOSI_GPIO_Port GPIOA
#define INT1_Pin GPIO_PIN_0
#define INT1_GPIO_Port GPIOE
#define INT1_EXTI_IRQn EXTI0_IRQn
#define INT2_Pin GPIO_PIN_1
#define INT2_GPIO_Port GPIOE
#define INT2_EXTI_IRQn EXTI1_IRQn

#define CS_HIGH HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET)
#define CS_LOW HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET)

/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                        0x00

//prototypes
void SPI_Init(void);
uint8_t SPIrw(uint8_t address, uint8_t data);
void SPIwrite(uint8_t address, uint8_t data);
uint8_t SPIread(uint8_t address);
