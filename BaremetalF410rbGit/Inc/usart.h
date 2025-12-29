/*
 * usart.h
 *
 *  Created on: Nov 15, 2025
 *      Author: baki
 */

#ifndef USART_H_
#define USART_H_

#include "baseAdress.h"
#include <stdint.h>

#define USART2_CR1OFFSET (0x0C)
#define USART2_CR1 		 (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_CR1OFFSET))

#define USART2_BAUDRATEREGISTER_OFFSET (0x08)
#define USART2_BRR		 (*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_BAUDRATEREGISTER_OFFSET))


#define USART2_SR_OFFSET (0x00)
#define USART2_SR		(*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_SR_OFFSET))

#define USART2_DATAREGISTER_OFFSET (0x04)
#define USART2_DR		(*(volatile unsigned int *)(USART2_PERIPHERAL + USART2_DATAREGISTER_OFFSET))







//prototypes

void usart2_init(void);
void usart2_write(int ch);
uint8_t usart2_read(void);
void usart_set_baudrate(uint32_t pclk, uint32_t baud);

#endif /* USART_H_ */
