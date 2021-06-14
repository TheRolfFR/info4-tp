/* 
 * File:   UART_LIN.c
 * Author: aravey
 *
 * Created on 12 april 2020, 13:42
 */

#include <string.h>
#include "UART_LIN.h"

USART_TypeDef* usart = USART3;

/********** MASTER/SLAVE Switch *********/
uint8_t master = 0;
/**
 * @brief Switches LIN to master
 */
void LIN_SetMaster() {
	master = 1;
	usart->CR2 &= ~USART_CR2_LBDIE;
}

/**
 * @brief Switches LIN to slave
 */
void LIN_SetSlave() {
	master = 0;
	usart->CR2 |= USART_CR2_LBDIE;
}

//UART_Init() sets up the UART for a 8-bit data, No Parity, 1 Stop bit
//at 9600 baud with transmitter interrupts enabled
void UART_Init (void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	// PB10 + PB11

	/* Setup PB10 + PB11 as Alternate Function */
	GPIOB->MODER &= ~(0xF << 20); // 1111
	GPIOB->MODER |=  (0xA << 20); // 1010

	// AF7
	/* Setup Alternate function as USART3 */
	GPIOB->AFR[1] &= ~(0xFF << 8);
	GPIOB->AFR[1] |=  (0x77 << 8);

	/* Push pull output */
	GPIOB->OTYPER &= ~(0x2 << 10);

	/* Pull up resistor on */
	GPIOB->PUPDR &= ~(0xF << 20);
	GPIOB->PUPDR |=  (0b0101 << 20);

	/* Output speed set to VeryHigh */
	GPIOB->OSPEEDR |= (0b1111 << 20);

	// activer usart
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	//Enable Tx and Rx
	usart->CR1 = USART_CR1_TE | USART_CR1_RE; // + add USART_CR1_RXNEIE but later
	// LIN + all LIN break interruptions, LBDL = 0 = 10-bit
	usart->CR2 = USART_CR2_LINEN; // + add USART_CR2_LBDIE but later
	// No control mode, 3 sample point,
	usart->CR3 = 0;
	// 9600bauds -> USARTDIV = (42mega)/(16*9600) = 273,4375 -> Mantissa = 273d=0x111 , Fraction = 0.4375*16 = 7d = 0x7
	usart->BRR = 0x00001117;
	//Enable UART + OOOOVERSAMPLING
	usart->CR1 |= USART_CR1_UE;

	/* USART interrupt Init */
	__enable_irq();
	NVIC_SetPriority(USART3_IRQn, 5);
	NVIC_EnableIRQ(USART3_IRQn);

	LIN_SetSlave();
}

uint8_t UART_GetChar() {
	while((usart->SR & USART_SR_RXNE) == 0);

	return (usart->DR & 0xFF);
}

void SendHeader(LINMSG *msg) {
	if(!master)
		return;

	sync_break();
	UART_PutChar(msg->ID);
}

void SendResponse(LINMSG *msg) {
	for(uint8_t di = 0; di < msg->length; ++di) {
		UART_PutChar(msg->data[di]);
	}
	UART_PutChar(checksum(msg->length, msg->data));
}

/*--- Transmit LIN Message ---*/
void SendMessage(LINMSG *msg)
{
	if(!master)
		return;

	SendHeader(msg);
	SendResponse(msg);
}

/*--- Transmit LIN Request ---*/
uint8_t lin_request_id = 0;
void SendRequest(uint8_t id)
{
	if(!master)
		return;

	//envoyer un header : sync_break + id
	sync_break();
	UART_PutChar(id);

	lin_request_id = id;

	// activer interruptions pour RXNE en attente de la réponse de l'esclave
	usart->CR1 |= USART_CR1_RXNEIE;
}

/********** Callback de réponse *********/
void (*lin_callback)(uint8_t) = NULL;
void LIN_SetReceiveCallback(void (*callback)(uint8_t)) {
	lin_callback = callback;
}

void USART3_IRQHandler() {
	if(master) {
		// si je suis maitre ce que je reçois c'est la réponse de l'esclave
		if((usart->CR1 & USART_CR1_RXNEIE) && (usart->SR & USART_SR_RXNE)) {
			// le pid reçu est donc celui de la requête que j'ai envoyé
			// je m'occuperai de filtrer le PID dans la reponse
			if(lin_callback != NULL)
				lin_callback(lin_request_id);

			// j'arrête d'écouter
			usart->CR1 &= ~USART_CR1_RXNEIE;
		}
	} else {
		uint8_t uart_byte;
		// si je suis esclave, je reçois une requête ou un message
		if((usart->CR2 & USART_CR2_LBDIE) && (usart->SR & USART_SR_LBD)) {

			// j'attend un 0 de mon break
			uart_byte = UART_GetChar();

			// j'attend le sync field
			uart_byte = UART_GetChar();

			// je vérifie la valeur du sync field
			if(uart_byte != 0x55) {
				usart->SR &= ~USART_SR_LBD;
				return; // Sync field incorrect
			}

			// j'attends le PID
			uart_byte = UART_GetChar();

			// je m'occuperai de filtrer le PID dans la reponse
			if(lin_callback)
				lin_callback(uart_byte);

			usart->SR &= ~USART_SR_LBD;
		}
	}
}

/*--- Send sync field and break ---*/

void sync_break(void)
{
	// notre break
	usart->CR1 |= USART_CR1_SBK;

	// sync field
	UART_PutChar(0x55);
}

/*--- Transmit char ---*/

void UART_PutChar(uint8_t data)
{
	//Load data to register
	USART3->DR = data;
	while (!(USART3->SR & USART_SR_TXE_Msk));
	while (!(USART3->SR & USART_SR_TC_Msk));
}

/*--- Calculate lin checksum ---*/

uint8_t checksum(uint8_t length, uint8_t *data)
{
	uint8_t ix;
	uint16_t check_sum = 0;

	for(ix = 0; ix < length-1; ix++)
	{
		check_sum += data[ix];
		if(check_sum >= 256){
			check_sum -= 255;
		}
	}

	return (uint8_t)(0xff - check_sum);
}
