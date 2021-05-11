/*
 * usart2.h
 *
 *  Created on: 13 sept. 2019
 *      Author: aravey
 */

#ifndef USART2_H_
#define USART2_H_

/*Functions Prototype */
void USART2_init(void);
void USART2_init_int(void);
void USART2_putc(char c);
void USART2_puts(char *msg);
void USART2_newline();
char USART2_getchar(void);
void USART2_Receive(char *data, uint32_t len);
signed int string2int(char *s);
char * int2string(signed int num);
char* float2string(float nombre, char *chaine);

#endif /* USART2_H_ */
