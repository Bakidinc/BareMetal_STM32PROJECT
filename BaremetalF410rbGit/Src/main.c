#include "gpio.h"
#include "baseAdress.h"
#include "stdint.h"
#include "usart.h"

int main(void)
{
    gpio_init();
    usart2_init();
    const char *msg = "HELLO";
    uint8_t prgrm_state = OFF;

    while (1)
    {

		usart2_write_string("HELLO\r\n");
		usart2_write('\r'); // Carriage Return
		usart2_write('\n'); // Line Feed
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
