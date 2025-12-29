/*
 * usart.c
 *
 *  Created on: Dec 15, 2025
 *      Author: Bakidinc 11111
 */
#include "usart.h"
#include <stdint.h>


#define CR1_UE		(1U<<13)//USART enable
#define CR1_RE		(1U<<2)//Receiver enable
#define CR1_TE		(1U<<3)//Transmitter enable
#define CR1_RXNEIE  (1U<<5)//RXNE interrupt enable
#define CR1_TXEIE	(1U<<7) // TXE interrupt enable

#define SR_RXNE		(1U<<5)//Read data register not empty
#define SR_TXE		(1U<<7)//Transmit data register empty

#define RCC_USART2_EN	(1U<<17)

#define SYS_CLK 16000000U

#define APB1_CLK		SYS_CLK
#define UART_BAUDRATE 	9600

void usart2_init(void){
	//GPIO çevresel birimine izin ver usart2 için(SAAT)
		RCC_APB1ENR  |= RCC_USART2_EN;

	//usart2 yi altarnatif fonksiyon olarak belirle
	//baudrate hızını ayarla
		usart_set_baudrate(SYS_CLK, UART_BAUDRATE);
	//tx ve rx tranfer fonksiyonlarını etkinleştir cr1 içindeki
		USART2_CR1 |=	CR1_TE;
		USART2_CR1 |= 	CR1_RE;

	//usart2 enable etme
		USART2_CR1 |=	CR1_UE;

}
void usart2_write(int ch) {
    uint32_t timeout = 100000;
    while(!(USART2_SR & SR_TXE) && timeout--) {
        ; // TXE bayrağı set olana kadar bekle
    }
    if(timeout > 0) {
        USART2_DR = ch;
    }
}

uint8_t usart2_read(void){
    while(!(USART2_SR & SR_RXNE))
        ;
    return (uint8_t)USART2_DR;
}
void usart_set_baudrate(uint32_t pclk, uint32_t baud)
{
    USART2_BRR = ((pclk + (baud/2U)) / baud);
}


