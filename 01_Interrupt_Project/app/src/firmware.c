#include <libopencm3/stm32/rcc.h> 
#include <libopencm3/stm32/gpio.h>
#include "core/system.h"

#define CPU_FREQ (84000000)
#define SYSTICK_FREQ (1000)



static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
}



/*static void delay_cycles(uint32_t delay)
{
    for (uint32_t i = 0; i < delay; i++)
    {
        __asm__("nop"); // Assembly No Operation
    }
}*/

/* Aslında delay_cycles burada 4 cycle'lik islem var
1-nop: (İşlem yapma) -> 1 Cycle
2-i++: (Sayacı 1 artır / ADD) -> 1 Cycle
3-i < delay: (Sayacı limit ile kıyasla / CMP) -> 1 Cycle
4-branch: (Başa dön / BNE) -> 1~2 Cycle (Pipeline durumuna göre)
toplam süre =(Toplam Tur Sayısı × Tur Başına Cycle) / İşlemci Hızı */

volatile static uint64_t start_time = 0;
int main(void)
{
    rcc_setup();
    gpio_setup();
    systick_setup();
    start_time = get_ticks();
    

    while (1)
    {
        if(get_ticks()-start_time >=1000){
            gpio_toggle(GPIOA, GPIO5);
            start_time =get_ticks();
        }
        
        //delay_cycles(84000000 / 4);
    }
    return 0;
}