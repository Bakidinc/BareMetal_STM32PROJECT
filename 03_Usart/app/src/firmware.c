#include <libopencm3/stm32/rcc.h> 
#include <libopencm3/stm32/gpio.h>
#include "core/system.h"
#include "core/timer.h"
  




static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO0);
    gpio_set_af(GPIOA,GPIO_AF2,GPIO0);
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
    system_setup();
    gpio_setup();
    timer_setup();
    
    start_time = system_get_ticks();
    float duty_cycle = 0.0f;
    

    while (1)
    {// Her 10 milisaniyede bir döngüye gir
       if (system_get_ticks() - start_time >= 500) {
            
            duty_cycle += 2.0f;
            
            if (duty_cycle > 100.0f) {
                duty_cycle = 0.0f;
            }

            // Hesaplanan değeri Timer'a yükle
            timer_pwm_set_duty_cycle(duty_cycle);

            start_time = system_get_ticks();
        }
    }
    return 0;
}