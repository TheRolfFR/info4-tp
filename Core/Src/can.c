/*
 * can.C
 *
 *  Created on: Mar 29, 2021
 *      Author: Ryan HADJ MEBAREK
 */
#include "can.h"
#include "usart2.h"

uint8_t IDE = 0;

void CAN_config(uint8_t extended, uint16_t Filter_ID_high,
		uint16_t Filter_ID_low, uint16_t Filter_Mask_high,
		uint16_t Filter_Mask_low) {

	IDE = extended;

	//Enable RCC clock for CAN1
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

	/*
	 CAN1 GPIO Configuration
	 PB8     ------> CAN1_RX
	 PB9     ------> CAN1_TX
	 */
	GPIOB->MODER &= ~(GPIO_MODER_MODER8_Msk | GPIO_MODER_MODER9_Msk); //AF mode for pin 8
	GPIOB->MODER |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1; //AF mode for pin 9
	GPIOB->AFR[1] |= GPIO_AFRH_AFRH0_0 | GPIO_AFRH_AFRH0_3; //AF9 for pin 8
	GPIOB->AFR[1] |= GPIO_AFRH_AFRH1_0 | GPIO_AFRH_AFRH1_3; //AF9 for pin 9
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9;

	/* Enter initialization mode */
	CAN1->MCR &= ~CAN_MCR_SLEEP;
	CAN1->MCR |= CAN_MCR_INRQ;

	/* Wait the acknowledge */
	while ((CAN1->MSR & CAN_MSR_INAK) != CAN_MSR_INAK)
		;

	CAN1->BTR = 16;
	CAN1->BTR |= CAN_MODE_NORMAL | CAN_BS1_6TQ | CAN_BS2_3TQ | CAN_SJW_1TQ; // sinon CAN_MODE_LOOPBACK

	/* Deactivate filter 0 */
	CAN1->FA1R &= ~CAN_FA1R_FACT0;

	/* Initialization mode for the filter */
	CAN1->FMR |= CAN_FMR_FINIT;

	/* 32 bits filter for filter 0 */
	CAN1->FS1R |= CAN_FS1R_FSC0;

	/* Filter 0 in mask mode */
	CAN1->FM1R &= ~(CAN_FM1R_FBM0);

	/* Filter 0 assigned to FIFO0 */
	CAN1->FFA1R &= ~(CAN_FFA1R_FFA0);

	CAN1->sFilterRegister[0].FR1 = ((0x0000FFFFU & Filter_ID_high) << 16)
			| (0x0000FFFFU & Filter_ID_low);

	CAN1->sFilterRegister[0].FR2 = ((0x0000FFFFU & Filter_Mask_high) << 16)
			| (0x0000FFFFU & Filter_Mask_low);

	/* Activate Filter 0 */
	CAN1->FA1R |= CAN_FA1R_FACT0;

	/* Disable filter initialization */
	CAN1->FMR &= ~CAN_FMR_FINIT;

	/* Enable Interrupt */
	CAN1->IER |= CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING;
	NVIC_SetPriority(CAN1_RX0_IRQn, 1);
	NVIC_EnableIRQ(CAN1_RX0_IRQn); // Enable FIFO 0 RX interrupt

	/* Request leave initialization */
	CAN1->MCR &= ~(CAN_MCR_INRQ);

	/* Wait the acknowledge
	 while ((CAN1->MSR & CAN_MSR_INAK) != 0U)
	 ;*/

}

uint8_t CAN_envoi(CAN_frame CAN_mes) {
	/* Get an empty mail box */
	uint32_t transmitmailbox;
	uint32_t tsr = CAN1->TSR;
	transmitmailbox = (tsr & CAN_TSR_CODE) >> CAN_TSR_CODE_Pos;

	if (CAN_mes.IDE == 0) {
		CAN1->sTxMailBox[transmitmailbox].TIR = ((CAN_mes.StdId
				<< CAN_TI0R_STID_Pos) | CAN_mes.RTR << 1);
	} else {
		CAN1->sTxMailBox[transmitmailbox].TIR = ((CAN_mes.ExtId
				<< CAN_TI0R_EXID_Pos) | CAN_mes.IDE | CAN_mes.RTR << 1);
	}

	/* Set up the DLC */
	CAN1->sTxMailBox[transmitmailbox].TDTR = (CAN_mes.DLC);
	/* Set up the data field */
	CAN1->sTxMailBox[transmitmailbox].TDHR = ((uint32_t) CAN_mes.Data[7]
			<< CAN_TDH0R_DATA7_Pos)
			| ((uint32_t) CAN_mes.Data[6] << CAN_TDH0R_DATA6_Pos)
			| ((uint32_t) CAN_mes.Data[5] << CAN_TDH0R_DATA5_Pos)
			| ((uint32_t) CAN_mes.Data[4] << CAN_TDH0R_DATA4_Pos);
	CAN1->sTxMailBox[transmitmailbox].TDLR = ((uint32_t) CAN_mes.Data[3]
			<< CAN_TDL0R_DATA3_Pos)
			| ((uint32_t) CAN_mes.Data[2] << CAN_TDL0R_DATA2_Pos)
			| ((uint32_t) CAN_mes.Data[1] << CAN_TDL0R_DATA1_Pos)
			| ((uint32_t) CAN_mes.Data[0] << CAN_TDL0R_DATA0_Pos);

	/* Request transmission */
	CAN1->sTxMailBox[transmitmailbox].TIR |= CAN_TI0R_TXRQ;

	return 1;
}

void CAN_printframe(CAN_frame fr) {
	USART2_puts("\r\nCAN_frame ");
	USART2_puts("{\r\n  STDID = ");
	USART2_puts(int2string(fr.StdId));
	USART2_puts(";\r\n  RTR: ");
	USART2_puts(int2string(fr.RTR));
	USART2_puts(";\r\n  DLC = ");
	USART2_puts(int2string(fr.DLC));
	USART2_puts(";\r\n  data = {");
	for (uint8_t i = 0; i < fr.DLC; ++i) {
		USART2_puts("\r\n    [");
		USART2_puts(int2string(i));
		USART2_puts("] = ");
		USART2_puts(int2string(fr.Data[i]));
		USART2_puts(";");
	}
	USART2_puts("\r\n  }\r\n}");
}
