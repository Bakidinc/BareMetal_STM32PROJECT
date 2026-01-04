/*
 * gpio.c
 *
 *  Created on: Nov 15, 2025
 *      Author: baki
 */


#include "gpio.h"
#include "stdint.h"

#define GPIOAEN	(1U<<0)
#define GPIOBEN	(1U<<1)
#define GPIOCEN	(1U<<2)

#define GPIOA8	(1U<<8)
#define GPIOB5	(1U<<5)
#define GPIOC13	(1U<<13)
#define GPIOA5	(1U<<5)

#define RED_LED	 	GPIOA8
#define BLUE_LED 	GPIOB5
#define USER_BUTTON	GPIOC13
#define USER_LED	GPIOA5
volatile int x ;

void gpio_init(void) {
    // GPIO saat erişimini etkinleştir
    RCC_AHB1ENR |= GPIOAEN;
    RCC_AHB1ENR |= GPIOBEN;
    RCC_AHB1ENR |= GPIOCEN;

    // LED pinleri
    GPIOA_MODER |= (1U << 16);
    GPIOA_MODER &= ~(1U << 17);

    GPIOB_MODER |= (1U << 10);
    GPIOB_MODER &= ~(1U << 11);

    GPIOC_MODER &= ~(1U << 26);
    GPIOC_MODER &= ~(1U << 27);

    GPIOA_MODER |= (1U << 10);
    GPIOA_MODER &= ~(1U << 11);

    // PA2 - USART2_TX (Alternate Function Mode)
    GPIOA_MODER &= ~(3U << (2 * 2));
    GPIOA_MODER |=  (2U << (2 * 2));

    // PA3 - USART2_RX (Alternate Function Mode)
    GPIOA_MODER &= ~(3U << (3 * 2));
    GPIOA_MODER |=  (2U << (3 * 2));

    // **ÖNEMLİ: Alternate Function Seçimi**
    // PA2 için AF7 (USART2_TX)
    GPIOA_AFRL &= ~(0xFU << (2 * 4));
    GPIOA_AFRL |=  (7U << (2 * 4));

    // PA3 için AF7 (USART2_RX)
    GPIOA_AFRL &= ~(0xFU << (3 * 4));
    GPIOA_AFRL |=  (7U << (3 * 4));

    GPIOA_MODER |=	(1U<<0);
    GPIOA_MODER |=	(1U<<1);



}
void red_led_on	(void){

	GPIOA_ODR |= RED_LED;


}
void red_led_off(void){

	GPIOA_ODR &= ~(RED_LED);
}
void blue_led_on(void){
	GPIOB_ODR|= BLUE_LED;
}
void blue_led_off(void){
	GPIOB_ODR &= ~(BLUE_LED);
}

void led_toggle(void){

	GPIOA_ODR ^= USER_LED;
	led_delay();
}

void prgrm_state_set(uint8_t *prgrm_state) {
	if (!(GPIOC_IDR & USER_BUTTON)) {
		if (*prgrm_state == ON) {
			*prgrm_state = OFF;
		} else if (*prgrm_state == OFF) {
			*prgrm_state = ON;
		}
	}
}
void prgrm_state_display(uint8_t *prgrm_state){

	if(*prgrm_state== ON){
		red_led_on();
		blue_led_off();
	}else if (* prgrm_state== OFF){
			red_led_off();
			blue_led_on();
		}

}

void led_delay(void){
	for(x=0 ; x<115000;x++){
		;
	}
}
