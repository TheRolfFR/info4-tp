/**
  * @brief  Init USART2 @ baud,8,1,n
  * @param  baud rate
  * @retval None
  * */

#include <stm32f4xx.h>
#include <stdio.h>
#include "usart.h"

/**
  * @brief  Init USART2 @ baud,8,1,n
  * @param  baud rate
  * @retval None
  * */
void USART2_Init(uint32_t baud)
{
	// 1. Configuration des GPIOs
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= 0x000000A0;
	GPIOA->MODER &= 0xFFFFFFAF;
	GPIOA->AFR[0] &= 0xFFFF77FF;
	GPIOA->AFR[0] |= 0x00007700;

	uint32_t tmp = 0, divmantissa, divfraction, apbclk;

	/* initialisation de l'USART2 : baud,8,1,n */

	/* reset/de-reset USART2 */
	RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
	/* enable USART2 clk */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	/*-------------- UART parameters configuration --------------- */
	USART2->CR1 &= ~USART_CR1_UE;
	/* USART CR1 Configuration : tx and rx enable; oversampling = 16 */
	USART2->CR1 = USART_CR1_TE | USART_CR1_RE;
	/* USART CR2 Configuration : 1 stop bit*/
	USART2->CR2 = 0 ;
	/* USART CR3 Configuration : no flow control*/
	USART2->CR3 = 0;
	/* USART BRR Configuration : depend on the bus frequency*/
	/* get APB1 prescaler to determine the USART clock frequency apbclk*/
	tmp = (RCC->CFGR & RCC_CFGR_PPRE1)>>10;
	if (tmp & 4){
		tmp =  (tmp & 3) + 1;
		apbclk = SystemCoreClock >> tmp;
	}
	else {
		apbclk = SystemCoreClock;
	}

	/* Tx/Rx baud = apbclk /(8*(2-OVER8)*USARTDIV) */
	tmp = (USART2->CR1 & USART_CR1_OVER8)>>15;
	if (tmp == 0) {
		/* OVER8 = 0, div by 16 */
		divmantissa = (apbclk/baud) >> 4;
		divfraction = (apbclk/baud) & 0xF;
	}
	else {
		/* OVER8 = 1, div by 8 */
		divmantissa = (apbclk/baud) >> 3;
		divfraction = (apbclk/baud) & 3;
	}
	/*USART2->BRR = mantissa and fraction part*/
	USART2->BRR = (divmantissa << 4) | divfraction ;


	/* enable USART */
	USART2->CR1 |= USART_CR1_UE;

	/* clear TC */
	USART2->SR |= USART_SR_TC;

	/*-------------- interrupt --------------- */
	//NVIC_SetPriority(USART2_IRQn,0x15); /*  priority */
	//NVIC_EnableIRQ(USART2_IRQn);
}

/**
  * @brief  De-Init USART2
  * @param  None
  * @retval None
  * */
void USART2_DeInit(void)
{

	/* reset/de-reset USART2 */
	RCC->APB1RSTR |= RCC_APB1RSTR_USART2RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_USART2RST;
	/* de-activate the USART2 clk */
	RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
}

/**
 * @brief Transmet la trame \p data de longueur \p length
 * @param data Pointeur vers le buffer d'octets à transmettre
 * @param length Longueur du buffer \p data
 * @retval None
 */
void USART2_Transmit(uint8_t * data, uint32_t length) {
	// éviter les pointeurs nuls et opérations inutiles
	if(data == 0x0 || length == 0)
		return;

	// j'attends que TC soit à un au cas où
	while((USART2->SR & USART_SR_TC) == 0);

	// j'envoie chaque caractère
	for(uint32_t i = 0; i < length; ++i) {
		__io_putchar((uint32_t) data[i]);
	}
}

/**
 * @brief Redéfinition de la sortie d'un caractère \p ch
 * @param ch le caractère à sortir
 * @retval le caractère sorti si succès
 */
int __io_putchar(int ch){
	// on attend que TX soit vide (empty)
	while((USART2->SR & USART_SR_TXE) == 0);

	// on écrit la valeur dans DR
	USART2->DR = ch;

	// j'attends d'être bien transmis
	while((USART2->SR & USART_SR_TC) == 0);

	// je me retourne car je me suis bien envoyé
	return ch;
}

/**
 * @brief Redéfinition de l'entrée d'un caractère
 * @retval le caractère reçu
 */
int __io_getchar(void) {
	// on attend d'être non vide (not empty) (bloquant)
	while((USART2->SR & USART_SR_RXNE) == 0);

	// je retourne la valeur trouvée
	return USART2->DR;
}

/**
 * @brief Bloque et reçoit une trame de maximum \p len caractères dans \data et sort si plus rien après \p delay
 * @param[out] data le buffer d'octets reçus
 * @param len taille du buffer \p data
 * @param delay délai d'attente après le premier caractère
 * @retval -1 si erreur de paramètre, taille effective du buffer sinon
 */
int32_t USART2_Receive(uint8_t * data, uint32_t len, uint32_t delay) {
	// éviter les pointeurs nuls et opérations inutiles
	if(data == 0x0 || len == 0)
		return -1;

	// je reçois le premier en mode bloquant
	data[0] = __io_getchar();
	int32_t effectiveSize = 1;

	//je démarre le compteur
	uint32_t counter = 0;

	// jusqu'à ce que je remplisse le buffer
	// ou que le délai soit dépassé
	while(effectiveSize < len && counter < delay) {
		if((USART2->SR & USART_SR_RXNE) == 0)
			// si j'ai rien j'incrémente le compteur
			++counter;
		else {
			// je prend l'octet le plus bas
			data[effectiveSize] = (USART2->DR & 0xFF);

			// j'augmente la taille effective
			++effectiveSize;

			// je redémarre le compteur
			counter = 0;
		}
	}

	// peu importe si le délai est dépassé,
	// je retourne la taille effective de ce que j'ai reçu
	return effectiveSize;
}

/**
 * @brief Transmits a single char
 * @param ch the character to send
 * @retval returns 0 if sent, 1 else
 */
uint8_t USART2_BigLoop_sendChar(uint8_t ch) {
	if((USART2->SR & USART_SR_TXE) == 0) {
		return 1;
	}

	// on écrit la valeur dans DR
	USART2->DR = ch;
	return 0;
}

/**
 * @brief returns if char has been sent (TC flag)
 * @retval 1 if sent, 0 else
 */
uint8_t USART2_BigLoop_isCharSent() {
//	0: Transmission is not complete
//	1: Transmission is complete
	return (USART2->SR & USART_SR_TC) >> USART_SR_TC_Pos;
}

uint8_t* data_pointer = NULL;
uint32_t data_index = 0;
uint32_t data_length = 0;
/**
 * @brief Set transmit buffer
 * @param data Data pointer to send
 * @param length Data size in bytes
 * @retval returns 0 if changed the buffer, 1 if parameter error
 */
uint8_t USART2_BigLoop_Transmit(uint8_t * data, uint32_t length) {
	// reject if invalid pointer or changed to different pointer when not finished
	if(data == NULL || (data_pointer != NULL && data != data_pointer && data_index < data_length))
		return 1;

	data_pointer = data;
	data_index = 0;
	data_length = length;

	return 0;
}

/**
 * @brief gradually transmits buffer
 * @retval returns 0 if char was sent, !=0 else
 */
uint8_t USART2_BigLoop_TransmitBuffer() {
	// if ended, nothing was sent or if the last char was not sent
	if(data_index == data_length || (!USART2_BigLoop_isCharSent()))
		return 1;

	// try to send the current char
	uint8_t ret = USART2_BigLoop_sendChar(data_pointer[data_index]);

	// if char not sent, return return value
	if(ret != 0)
		return ret;

	// else it was
	++data_index;

	return ret;
}

/**
 * @brief tells you if buffer totally sent
 * @retval 1 if true, 0 else
 */
uint8_t USART2_BigLoop_TransmitEnded() {
	return data_pointer != 0 && data_index == data_length && USART2_BigLoop_isCharSent();
}

uint8_t* receive_buffer = NULL;
uint32_t receive_index;
uint32_t receive_length = 0;
/**
 * @brief Set up receive buffer
 * @param data Data pointer to receive
 * @param length Data size in bytes
 * @retval returns 0 if setted up buffer, !=0 else
 */
uint8_t USART2_BigLoop_Receive(uint8_t * data, uint32_t length) {
	// reject if invalid pointer or changed to different pointer when not finished
	if(data == NULL || length == 0)
		return 1;

	receive_buffer = data;
	receive_index = 0;
	receive_length = length;

	return 0;
}

/**
 * @brief gradually receive buffer
 * @retval returns 0 if char was receive, !=0 else
 */
uint8_t USART2_BigLoop_ReceiveBuffer() {
	// if full nope
	if(receive_index == receive_length)
		return 1;

	// if empty nope
	if((USART2->SR & USART_SR_RXNE) == 0)
		return 1;

	// get it
	receive_buffer[receive_index++] = (USART2->DR & 0xFF);

	// get out
	return 0;
}

/**
 * @brief Check receive buffer size
 * @retval returns 1 if full, 0 else
 */
uint8_t USART2_BigLoop_ReceiveFull() {
	return receive_buffer != 0 && receive_index == receive_length;
}

/**
 * @Brief send a buffer in non-blocking way
 * @retval returns 0 if changed the buffer, 1 if parameter error
 */
uint8_t USART2_transmit_IRQ (uint8_t* buffer, uint32_t len) {
	uint32_t ret = USART2_BigLoop_Transmit(buffer, len);

	if(ret == 0) {
		USART2->CR1 |= USART_CR1_TXEIE;
	}

	return ret;
}
