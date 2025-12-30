/*
 * adc.c
 *
 *  Created on: Nov 15, 2025
 *      Author: baki
 */
#include "adc.h"

#define ADC_SR_EOC 		(1<<1)
#define ADC_CR2_ADON	(1<<0)
#define ADC_CR2_SWSTART (1<<30)
#define ADC_CR2_CONT	(1<<1)
#define ADC_SQR1_L_Msk   (0xF << 20)
#define ADC_SQR3_SQ1_Msk   (0x1F << 0)
