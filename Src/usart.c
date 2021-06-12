/**
  * @brief  Init USART2 @ baud,8,1,n
  * @param  baud rate
  * @retval None
  * */

#include <stm32f4xx.h>
#include "usart.h"

/**
  * @brief  Init USART2 @ baud,8,1,n
  * @param  baud rate
  * @retval None
  * */
void USART2_Init(uint32_t baud)
{
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
