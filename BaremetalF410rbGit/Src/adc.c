/*
 * adc.c
 *
 *  Created on: Nov 15, 2025
 *      Author: baki
 */
#include "adc.h"
#include "usart.h"


#define ADC_SR_EOC 			(1<<1)
#define ADC_CR2_ADON		(1<<0)
#define ADC_CR2_SWSTART 	(1<<30)
#define ADC_CR2_CONT		(1<<1)
#define ADC_SQR1_L_Msk   	(0xF << 20)
#define ADC_SQR3_SQ1_Msk	(0x1F << 0)
#define RCC_ADCEN			(1<<8)


void adc_init(void){
	//ADC modulune saat iznini ver enable et
	RCC_APB2 |= RCC_ADCEN;

	//gpio.c dosyasında GPIOA0'ı analog olarak ayarla
	//   GPIOA_MODER |=	(1U<<0); gpio.c de yapildi
    //   GPIOA_MODER |=	(1U<<1);


	// veri çözünürlüğünü ayarla

	ADC_CR1 |= (1<<24);
	ADC_CR1 &= ~(1<<25);

	//kanalı seç
	// 1. Adım: SQR3 register'ının ilk 5 bitini (SQ1) temizle/sıfırla
	ADC_SQR3 &= ~(0x1F);

	// 2. Adım: Kanal 0'ı seçmek için oraya '0' değerini yaz (Matematiksel olarak etkisiz olsa da mantığı budur)
	ADC_SQR3 |= (0 << 0);
	// adc modülünü etkinleştir

	ADC_CR2 |= ADC_CR2_ADON;
}
void adc_conversion(void){
	//Continuous moda ayarla
	ADC_CR2 |= ADC_CR2_CONT;

	//donusumu baslat

	ADC_CR2 |=ADC_CR2_SWSTART;

}
uint8_t adc_read(void){

	while(!(ADC_SR & ADC_SR_EOC)){
		;
	}

	return ADC_DR;
}

void adc_sample_signal(char *buff, uint8_t prgrm_state){
	char byte_one;
	int uart_byte;

	if(prgrm_state == ON){
		char *ptr = buff;

		for (int x = 0; x < 64; x++){

			uart_byte = adc_read();
			byte_one = (uart_byte & 0xFF);


			*buff++ = byte_one;
		}

        // ptr başlangıç adresini tutuyordu, onu gönderiyoruz.
		adc_transmit_signal(ptr);
	}
}
void adc_transmit_signal(char * buff){

	for(int x = 0; x < 64; x++){
		// 1. Diziden ham veriyi al (Örn: Sayısal 65)
		uint8_t number = (uint8_t)(*buff++);

		// 2. Yüzler, Onlar ve Birler basamağını hesapla
		// '0' eklememizin sebebi, rakamı ASCII karaktere çevirmektir.
		char hundreds = (number / 100) + '0';
		char tens     = ((number % 100) / 10) + '0';
		char ones     = (number % 10) + '0';

		// 3. Basamakları sırayla gönder
		usart2_write(hundreds);
		usart2_write(tens);
		usart2_write(ones);

		// 4. Okunabilir olsun diye yanına boşluk veya alt satır ekle
		// Alt satıra geçmek için:
		usart2_write('\r');
		usart2_write('\n');

		// Eğer yan yana yazdırmak istersen yukarıdaki \r\n yerine:
		// usart2_write(' '); // Boşluk
	}
}
