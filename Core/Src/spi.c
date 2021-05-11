/*
 * spi.c
 *
 *  Created on: 18 f�vr. 2020
 *      Author: aravey
 */

#include "spi.h"

void SPI_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/**SPI1 GPIO Configuration
	 PA5     ------> SPI1_SCK
	 PA6     ------> SPI1_MISO
	 PA7     ------> SPI1_MOSI
	 */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/**LIS3DSH ChipSelect Configuration
	 PE3     ------> LIS3DSH_SS
	 */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	/*Configure GPIO pin : CS_I2C_SPI_Pin */
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/**
	 * SPI1 configuration
	 */
	/* Peripheral clock enable */
	__HAL_RCC_SPI1_CLK_ENABLE();
	// SPI1 clock = APB2, prescaler set to 16 -> 84000000/16 = 5Mhz
	SPI1->CR1 = 0b000001101011100; //0x007E
	SPI1->CR2 = 0b0000000000000000; //0x0000
	// SPI1->I2SCFGR = 0; // SPI enable I2S disable
	// SPI1->I2SPR = 0b0000000000000000;
}

// Write a data @ address with SPI1
void SPIwrite(uint8_t address, uint8_t data) {
	CS_LOW; //CS --> Low
	HAL_Delay(1);
	SPI1->DR = address;
	HAL_Delay(1);
	while (!(SPI1->SR & 0x2))
		; // wait Flag TXE = 1
	while ((SPI1->SR & 0x80))
		; // wait Flag BSY = 0
	SPI1->DR = data;
	HAL_Delay(1);
	while (!(SPI1->SR & 0x2))
		; // Wait Flag TXE = 1
	while ((SPI1->SR & 0x80))
		; // wait Flag BSY = 0
	HAL_Delay(1);
	CS_HIGH; //CS --> High
}

// Write a data and read tempdat @ address with SPI1
uint8_t SPIrw(uint8_t address, uint8_t data) {
	uint8_t tempdat;
	CS_LOW; //CS --> Low
	HAL_Delay(1);
	SPI1->DR = address;
	HAL_Delay(1);
	while (!(SPI1->SR & 0x2))
		; // wait Flag TXE = 1
	while ((SPI1->SR & 0x80))
		; // wait Flag BSY = 0
	tempdat = SPI1->DR & 0xFF;
	HAL_Delay(1);
	SPI1->DR = data;
	HAL_Delay(1);
	while (!(SPI1->SR & 0x2))
		; // Wait Flag TXE = 1
	while ((SPI1->SR & 0x80))
		; // wait Flag BSY = 0
	tempdat = SPI1->DR & 0xFF;
	HAL_Delay(1);
	CS_HIGH; //CS --> High
	return tempdat;
}

// Write a tempdat @ address with SPI1
uint8_t SPIread(uint8_t address) {
	uint8_t tempdat;
	CS_LOW; //CS --> Low
	// HAL_Delay(100);
	SPI1->DR = address;
	while (!(SPI1->SR & 0x2))
		; // wait Flag TXE = 1
	while ((SPI1->SR & 0x80))
		; // wait Flag BSY = 0
	//HAL_Delay(100);
	tempdat = SPI1->DR & 0xFF; // Read dummy
	SPI1->DR = DUMMY_BYTE;
	while (!(SPI1->SR & 0x1))
		; // Wait Flag RXE = 1
	while ((SPI1->SR & 0x80))
		; // wait Flag BSY = 0
	// HAL_Delay(100);
	tempdat = SPI1->DR & 0xFF;
	// HAL_Delay(100);
	CS_HIGH; //CS --> High
	return tempdat;
}
