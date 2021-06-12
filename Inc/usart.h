void USART2_Init(uint32_t baud);
void USART2_DeInit(void);
int __io_putchar(int ch);
void USART2_Transmit(uint8_t * data, uint32_t length);
int __io_getchar(void);
int32_t USART2_Receive(uint8_t * data, uint32_t len, uint32_t delay);
