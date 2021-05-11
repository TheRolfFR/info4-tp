/*
 * acc.c
 *
 *  Created on: 22 mars 2021
 *      Author: achil
 */

#include "spi.h"
#include "acc.h"
#include "usart2.h"

void ACC_GPIO_init() {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : CS_Pin for ACC */
	GPIO_InitStruct.Pin = CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CS_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : INT1_Pin INT2_Pin for ACC*/
	GPIO_InitStruct.Pin = INT1_Pin | INT2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pin : PA0  for RTC*/
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void ACC_printData(struct coord *data) {
	//envoyer donnees sur UART
	char *chaine;

	USART2_puts("x :");
	chaine = int2string(data->x);
	USART2_puts(chaine);
	USART2_newline();

	USART2_puts("y :");
	chaine = int2string(data->y);
	USART2_puts(chaine);
	USART2_newline();

	USART2_puts("z :");
	chaine = int2string(data->z);
	USART2_puts(chaine);
	USART2_newline();
}

void ACC_Setup(void) {
	SPI_Init(); // initialiser le SPI pour l'acc
	ACC_GPIO_init(); // initialiser les GPIO acc

	if (SPIread(RD_MASK | WHO_AM_I) == WAI_DEF) { //verifier valeur par defaut de WHO_AM_I
		/*Data configuration*/
		//Lire deux fois pour pouvoir lire les données ensuite
		SPIread(RD_MASK | CTRL_REG5);
		SPIread(RD_MASK | CTRL_REG5);

		//Ecrire valeurs dans CTRL_REG5
		//default BW, 2g scale, self stale disabled, SPI 4Wires
		SPIwrite(WR_MASK & CTRL_REG5, 0x00);

		//Ecrire valeurs dans CTRL_REG4
		//400Hz data rate, continuous update, axis enabled
		SPIwrite(WR_MASK & CTRL_REG4, 0x77);

		/*SM & Int configuration*/
		//Ecrire valeurs dans CTRL_REG1
		//hysteresis 0, SM1 interrupt to INT2, SM1 enabled
		SPIwrite(WR_MASK & CTRL_REG1, 0x09);

		//Ecrire valeurs dans CTRL_REG3
		//DRDY disabled, int HIGH, int latched, INT2 enabled, INT1 disabled, VFILT disabled, no soft reset
		SPIwrite(WR_MASK & CTRL_REG3, 0x70); //50

		//Ecrire valeurs dans THRS1
		//SPIwrite(WR_MASK & THRS2_1, 0x00);
		SPIwrite(WR_MASK & THRS1_1, 0x55);

		//Ecrire etapes dans State Machine 1
		SPIwrite(WR_MASK & STx_1, 0x05); //no reset (nop); next : >THRS1 = wait for any value to be above threshold
		SPIwrite((WR_MASK & STx_1) + 1, 0x11); //CONT command : generate interrupt and restart

		//Ecrire valeurs dans MASK1
		//all axis enabled, no vector
		SPIwrite(WR_MASK & MASK1_B, 0xFC);
		SPIwrite(WR_MASK & MASK1_A, 0xFC);

		//Ecrire valeurs dans SETT1
		//no peak detection, no threshold3, unsigned, R_TAM disabled, program flow modified by STOP/CONT
		SPIwrite(WR_MASK & SETT1, 0x01);

	}
	CS_SET;
}

coord ACC_get_coord(void) {

	coord XYZ;

	//lire coordonees depuis registres accelerometre
	XYZ.x = SPIread(RD_MASK | OUT_X_LOW)
			| (SPIread(RD_MASK | (OUT_X_LOW + 1)) << 8);
	XYZ.y = SPIread(RD_MASK | OUT_Y_LOW)
			| (SPIread(RD_MASK | (OUT_Y_LOW + 1)) << 8);
	XYZ.z = SPIread(RD_MASK | OUT_Z_LOW)
			| (SPIread(RD_MASK | (OUT_Z_LOW + 1)) << 8);

	return XYZ;

}

