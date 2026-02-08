#include "timer.h" 
#include "libopencm3/stm32/timer.h"
#include <libopencm3/stm32/rcc.h> 

#define PRESCALER (84)
#define ARR_VALUE (1000)

//STM32 NUCLEO F410 ici yapilandirilmistir

void timer_setup(void){
    // Timer 5'in saatini aç
    rcc_periph_clock_enable(RCC_TIM5);

    // Timer modu ayarları (Yukarı sayım, clock division vs)
    timer_set_mode(TIM5, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    // PWM Modu 1 seçildi (Channel 1 için)
    timer_set_oc_mode(TIM5, TIM_OC1, TIM_OCM_PWM1);

    // PWM Çıkışını aktif et
    timer_enable_oc_output(TIM5, TIM_OC1);
    
    // Timer sayacını başlat
    timer_enable_counter(TIM5);

    // Frekans ayarlamaları
    // 84MHz / 84 = 1 MHz Timer hızı
    timer_set_prescaler(TIM5, PRESCALER - 1);
    // 1 MHz / 1000 = 1 kHz PWM frekansı (LED için ideal)
    timer_set_period(TIM5, ARR_VALUE - 1);
}

void timer_pwm_set_duty_cycle(float duty_cycle){
    // Duty cycle hesaplaması
    const float raw_value = (float)ARR_VALUE * (duty_cycle / 100.0f);
    
    // Channel 1 (PA0) için değeri set et
    timer_set_oc_value(TIM5, TIM_OC1, (uint32_t)raw_value);
}