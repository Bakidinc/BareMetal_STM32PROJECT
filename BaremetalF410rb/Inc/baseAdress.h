/*
 * baseAdress.h
 *
 *  Created on: Nov 15, 2025
 *      Author: baki
 */

#ifndef BASEADRESS_H_
#define BASEADRESS_H_

// Ana çevrebirim bloğunun başlangıç adresi
#define PERIPHERAL_BASE     (0x40000000UL)

/* * APB1 Veriyolu Adresleri
 * Adres: 0x4000 0000
 * Sapma (Offset): 0x40000000 - 0x40000000 = 0x0000
 */
#define APB1_OFFSET         (0x00000000UL)
#define APB1_PERIPHERAL     (PERIPHERAL_BASE + APB1_OFFSET)



/* * APB2 Veriyolu Adresleri
 * Adres: 0x4001 0000
 * Sapma (Offset): 0x40010000 - 0x40000000 = 0x00010000
 */
#define APB2_OFFSET         (0x00010000UL)
#define APB2_PERIPHERAL     (PERIPHERAL_BASE + APB2_OFFSET)

/* AHB1 Veriyolu Adresleri (GPIO'lar genelde buradadır)
 * Adres: 0x4002 0000
 * Sapma (Offset): 0x40020000 - 0x40000000 = 0x00020000
 */
#define AHB1_OFFSET         (0x00020000UL)
#define AHB1_PERIPHERAL     (PERIPHERAL_BASE + AHB1_OFFSET)


/*ADC1 Veriyolu adresi
 * Adres:0x4001 2000
 * Sapma(offset): 0x40012000 -0x40000000 =0x00012000
 */
#define ADC1_OFFSET			(0x00012000UL)
#define ADC1_PERIPHERAL		(PERIPHERAL_BASE + ADC1_OFFSET)

/*USART2 Veriyolu adresi
 * Adres:0x4000 4400
 * Sapma(offset): 0x4000 4400 -0x40000000 =0x00004400
 */

#define USART2_OFFSET		(0x00004400UL)
#define USART2_PERIPHERAL	(APB1_PERIPHERAL + USART2_OFFSET )

/*GPIO A-B-C Veriyolu adresi
 * GPIOA Adres:0x4002 0000
 * GPIOB Adres:0x4002 0400
 * GPIOC Adres:0x4002 0800
 */

#define GPIOA_OFFSET		(0x00020000UL)
#define GPIOA_PERIPHERAL	(PERIPHERAL_BASE + GPIOA_OFFSET)

#define GPIOB_OFFSET		(0x00020400UL)
#define GPIOB_PERIPHERAL	(PERIPHERAL_BASE + GPIOB_OFFSET)

#define GPIOC_OFFSET		(0x00020800UL)
#define GPIOC_PERIPHERAL	(PERIPHERAL_BASE + GPIOC_OFFSET)

//RCC
//RCC ADRES: 0x4002 3800

#define RCC_PERIPHERAL_OFFSET (0x00003800)
#define RCC_PERIPHERAL	  	  (AHB1_PERIPHERAL + RCC_PERIPHERAL_OFFSET)

#define RCC_APB1ENR_OFFSET 0x40
#define RCC_APB1ENR (*(volatile unsigned int *)(APB1_PERIPHERAL + RCC_APB1ENR_OFFSET))

enum State{
	OFF=48,
	ON=49
};

#endif /* BASEADRESS_H_ */
