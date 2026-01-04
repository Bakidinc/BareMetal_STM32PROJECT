#include "gpio.h"
#include "baseAdress.h"
#include "stdint.h"
#include "usart.h"
#include "adc.h"

void usart2_write_string(const char *str);
char buff[64];
char adc_value;
int main(void)
{
    gpio_init();
    usart2_init();
    adc_init();
    adc_conversion();

    uint8_t prgrm_state = OFF;

    while (1)
    {

    	//usart2_write_string("HELLO\r\n");

         prgrm_state_set(&prgrm_state);
         prgrm_state_display(&prgrm_state);
    	adc_sample_signal(buff, prgrm_state);
		adc_value=buff[0];
		for (volatile int i = 0; i < 1000000; i++)
			;

        // LED işlemleri
        //led_toggle();
       // prgrm_state_set(&prgrm_state);
        //prgrm_state_display(&prgrm_state);



    }
}
void usart2_write_string(const char *str)
{
    while (*str)
    {
        usart2_write(*str++);
    }
}
