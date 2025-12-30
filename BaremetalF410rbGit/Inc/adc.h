/*
 * adc.h
 *
 *  Created on: Nov 15, 2025
 *      Author: baki
 */

#ifndef ADC_H_
#define ADC_H_

#include "baseAdress.h"

#define ADC_SR_OFFSET  0x00
#define ADC_SR	(*(volatile unsigned int *)(ADC1_PERIPHERAL +ADC_SR_OFFSET))

#define ADC_CR2_OFFSET 0x08
#define ADC_SR	(*(volatile unsigned int *)(ADC1_PERIPHERAL +ADC_CR2_OFFSET))

#define ADC_SQR1_OFFSET  0x2C
#define ADC_SQR1		(*(volatile unsigned int *)(ADC1_PERIPHERAL +ADC_SQR1_OFFSET))

#define ADC_SQR3_OFFSET  0x34
#define ADC_SQR3		(*(volatile unsigned int *)(ADC1_PERIPHERAL +ADC_SQR3_OFFSET))


#define ADC_SR_EOC 		(1<<2)
#define ADC_CR2_ADON	(1<<0)
#define ADC_CR2_SWSTART (1<<30)
#define ADC_CR2_CONT	(1<<1)

#endif /* ADC_H_ */
