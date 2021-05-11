/*
 * i2c.c
 *
 *  Created on: 12 févr. 2020
 *      Author: aravey
 */

#include "i2c.h"

void init_I2C1(void) {

	/* Peripheral clock enable */
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	/* GPIOB clock enable */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	//GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/**I2C1 GPIO Configuration
	 PB6     ------> I2C1_SCL
	 PB9     ------> I2C1_SDA
	 */
	GPIOB->MODER |= GPIO_MODER_MODER6_Msk | GPIO_MODER_MODER9_Msk;
	GPIOB->MODER &= ~(GPIO_MODER_MODER6_0 | GPIO_MODER_MODER9_0); // Enable alternative function mode
	GPIOB->AFR[0] |= GPIO_AFRL_AFRL6_2;
	GPIOB->AFR[1] |= GPIO_AFRH_AFRH1_2;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_Msk | GPIO_OSPEEDR_OSPEED9_Msk;
	GPIOB->OTYPER |= GPIO_OTYPER_OT6 | GPIO_OTYPER_OT9;

	//Reset I2C peripheral
	I2C1->CR1 |= 0x8000;
	I2C1->CR1 &= 0x7FFF;

	//Set I2C mode, no SMB, no PEC, no ARP
	I2C1->CR1 = 0x0000;

	//APB1 = 42Mhz => FREQ=42; no interrupts
	I2C1->CR2 = 0x002A;

	//No slave mode, addr sets to 0
	I2C1->OAR1 = 0x4033;
	I2C1->OAR2 = 0;

	//Standard mode (Sm), Duty cycle = 2 (50%), CLock 100kHz=5000ns (one semi period) -> CCR= 42000000 * 0.000005000 = 210
	I2C1->CCR = 0x00D2;

	// TRISE set to 1000ns -> 42Mhz = 23.8ns : (1000/23.8)+1 = 43
	I2C1->TRISE = 0x002B;

	//Start I2C
	I2C1->CR1 |= 0x0001;
}

void I2C_Master_Transmit(uint8_t addr, uint8_t *buffer, uint8_t size) {

	uint8_t i = 0;

	//Wait for I2C bus to be free (not busy)
	while (I2C1->SR2 & 0x2)
		;

	//Send a start
	I2C1->CR1 |= 0x0100;
	// wait for start to finish -> SB = 1
	while (!(I2C1->SR1 & 0x1))
		;
	I2C1->DR = addr;
	//Wait until ADDR flag is set
	while (!(I2C1->SR1 & 0x2))
		;
	//Clear Addr flag (by reading SR1 then SR2)
	if (I2C1->SR1 == 0x0)
		;
	if (I2C1->SR2 == 0x0)
		;

	while (size > 0) {
		// Wait for Txe (register Empty)
		while (!(I2C1->SR1 & 0x0080))
			;
		//Write to DR
		I2C1->DR = buffer[i];
		size = size - 1;
		i = i + 1;
		//Check if BTF ==1
		if ((I2C1->SR1 & 0x0004) && size > 0) {
			//Write to DR
			I2C1->DR = buffer[i];
			size = size - 1;
			i = i + 1;
		}
	}
	//Wait BTF to be set
	while (!(I2C1->SR1 & 0x0004))
		;
	//Send a stop byte
	I2C1->CR1 |= 0x0200;
	// Wait stop to be sent
	while ((I2C1->SR1 & 0x0010))
		;
}

void I2C_Master_Receive(uint8_t addr, uint8_t *buffer, uint8_t size) {

	uint8_t i = 0;

	//Wait for I2C bus to be free (not busy)
	while (I2C1->SR2 & 0x2)
		;

	//Disable POS
	I2C1->CR1 &= 0xFEFF;

	//Enable Ack
	I2C1->CR1 |= 0x0400;
	//Send a start
	I2C1->CR1 |= 0x0100;
	// wait for start to finish -> SB = 1
	while (!(I2C1->SR1 & 0x1))
		;
	I2C1->DR = addr;
	//Wait until ADDR flag is set
	while (!(I2C1->SR1 & 0x2))
		;

	if (size == 0) {
		//Clear Addr flag (by reading SR1 then SR2)
		if (I2C1->SR1 == 0x0)
			;
		if (I2C1->SR2 == 0x0)
			;
		//Send a stop byte
		I2C1->CR1 |= 0x0200;
	} else if (size == 1) {
		// In this case, we receive only 1 data, we need to NOack it
		//Disable Ack
		I2C1->CR1 &= 0xFBFF;

		//Clear Addr flag (by reading SR1 then SR2)
		if (I2C1->SR1 == 0x0)
			;
		if (I2C1->SR2 == 0x0)
			;

		//Send a stop byte
		I2C1->CR1 |= 0x0200;
	} else {
		//Enable Ack
		I2C1->CR1 |= 0x0400;
		//Clear Addr flag (by reading SR1 then SR2)
		if (I2C1->SR1 == 0x0)
			;
		if (I2C1->SR2 == 0x0)
			;
	}

	while (size > 0) {
		if (size <= 3) {
			// We received only one byte
			if (size == 1) {
				//Wait RXNE=1 to receive a byte
				while (!(I2C1->SR1 & 0x0040))
					;
				//Read data
				buffer[i] = I2C1->DR;
				size = size - 1;
				i = i + 1;
			}
			// We received two bytes
			else if (size == 2) {

				//Wait RXNE=1 to receive a byte
				while (!(I2C1->SR1 & 0x0040))
					;

				//Disable Ack
				I2C1->CR1 &= 0xFBFF;
				//Send a stop byte
				I2C1->CR1 |= 0x0200;

				//Read data
				buffer[i] = I2C1->DR;
				size = size - 1;
				i = i + 1;

				//Wait RXNE=1 to receive a byte
				while (!(I2C1->SR1 & 0x0040))
					;

				//Read data
				buffer[i] = I2C1->DR;
				size = size - 1;
				i = i + 1;

				// Wait stop to be sent
				while ((I2C1->SR1 & 0x0010))
					;
			}
			// We received 3 bytes
			else {
				//Wait BTF = 1
				while (!(I2C1->SR1 & 0x0004))
					;

				//Disable Ack
				I2C1->CR1 &= 0xFBFF;

				//Read data
				buffer[i] = I2C1->DR;
				size = size - 1;
				i = i + 1;

				//Wait BTF = 1
				while (!(I2C1->SR1 & 0x0004))
					;

				//Send a stop byte
				I2C1->CR1 |= 0x0200;

				//Read data
				buffer[i] = I2C1->DR;
				size = size - 1;
				i = i + 1;

				//Read data
				buffer[i] = I2C1->DR;
				size = size - 1;
				i = i + 1;
			}
		} else {
			//Wait RXNE=1 to receive a byte
			while (!(I2C1->SR1 & 0x0040))
				;

			//Read data
			buffer[i] = I2C1->DR;
			size = size - 1;
			i = i + 1;

			//If BTF is set
			if (I2C1->SR1 & 0x0004) {
				//Read data
				buffer[i] = I2C1->DR;
				size = size - 1;
				i = i + 1;
			}
		}
	}
}

void I2C_Slave_Receive(uint8_t *buffer, uint8_t size) {
	uint8_t i = 0;
	// Enable Acknowledge for Address reception
	I2C1->CR1 |= 0x0400;

	//Disable POS
	I2C1->CR1 &= 0xFEFF;

	//Wait for Addr flag (Master send the good address to slave)
	while (!(I2C1->SR1 & 0x2))
		;

	//Clear Addr flag (by reading SR1 then SR2)
	if (I2C1->SR2 == 0x0)
		;

	while (size > 0) {
		//Wait for Rxne
		while (!(I2C1->SR1 & 0x0040))
			;
		//Read data
		buffer[i] = I2C1->DR;
		size = size - 1;
		i = i + 1;

		//Check if BTF = 1 (we received 2 data)
		if (I2C1->SR1 & 0x0004) {
			//Read data
			buffer[i] = I2C1->DR;
			size = size - 1;
			i = i + 1;
		}

	}

	//Wait until STOP flag
	while (!(I2C1->SR1 & 0x0010))
		;
}
