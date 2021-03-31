void USART2_Init(uint32_t baud);
void USART2_DeInit(void);
int __io_putchar(int ch);
void USART2_Transmit(uint8_t * data, uint32_t length);
int __io_getchar(void);
int32_t USART2_Receive(uint8_t * data, uint32_t len, uint32_t delay);


/**
 * @brief returns if char has been sent (TC flag)
 * @retval 1 if sent, 0 else
 */
uint8_t USART2_BigLoop_isCharSent();

/**
 * @brief Transmits a single char
 * @param ch the character to send
 * @retval returns 0 if sent, 1 else
 */
uint8_t USART2_BigLoop_sendChar(uint8_t ch);

/**
 * @brief Set transmit buffer
 * @param data Data pointer to send
 * @param length Data size in bytes
 * @retval returns 0 if changed the buffer, 1 if parameter error
 */
uint8_t USART2_BigLoop_Transmit(uint8_t * data, uint32_t length);

/**
 * @brief gradually transmits buffer
 * @retval returns 0 if char was sent, !=0 else
 */
uint8_t USART2_BigLoop_TransmitBuffer();

/**
 * @brief tells you if buffer totally sent
 * @retval 1 if true, 0 else
 */
uint8_t USART2_BigLoop_TransmitEnded();

/**
 * @brief Transmits a single char
 * @param data Data pointer to send
 * @param length Data size in bytes
 * @retval returns 0 if filled buffer, 1 else
 */
uint8_t USART2_BigLoop_Receive(uint8_t * data, uint32_t length);


/**
 * @brief Check receive buffer size
 * @retval returns 1 if full, 0 else
 */
uint8_t USART2_BigLoop_ReceiveFull();
