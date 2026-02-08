#ifndef SYSTEM_H
#define SYSTEM_H

#include "common-defines.h" 

#define CPU_FREQ (84000000)
#define SYSTICK_FREQ (1000)
// Sistem saatini yapılandırmak için fonksiyon prototipi
void system_setup(void);

uint64_t system_get_ticks(void );

// Basit bir milisaniye geciktirme fonksiyonu
void system_delay(uint32_t ms);
void sys_tick_handler(void );
void systick_setup(void);
void rcc_setup(void);

#endif // SYSTEM_H