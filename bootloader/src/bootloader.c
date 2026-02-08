#include "common-defines.h"
#include <libopencm3/stm32/memorymap.h>
#include <libopencm3/cm3/scb.h> // SCB_VTOR için gerekli

// Bootloader için ayırdığın alan (32KB)
#define BOOTLOADER_SIZE         (0x8000U)
// Uygulamanın başladığı gerçek adres (0x08008000)
#define MAIN_APP_START_ADDRESS  (FLASH_BASE + BOOTLOADER_SIZE)

static void jump_to_main(void) {
    // 1. Uygulamanın vektör tablosundan Reset Handler adresini al
    // Vektör tablosunda: [0]: MSP, [4]: Reset Handler
    uint32_t *reset_vector_entry = (uint32_t *)(MAIN_APP_START_ADDRESS + 4U);
    uint32_t *app_stack_ptr = (uint32_t *)(MAIN_APP_START_ADDRESS);

    // 2. Reset Handler fonksiyon pointer'ını oluştur
    void (*app_reset_handler)(void) = (void (*)(void))(*reset_vector_entry);

    // 3. SCB_VTOR register'ını güncelle (En kritik nokta!)
    // İşlemciye kesme tablosunun artık uygulama adresinde olduğunu söyler.
    // SCB_VTOR makrosu libopencm3 içinde tanımlıdır (0xE000ED08).
    SCB_VTOR = MAIN_APP_START_ADDRESS;

    // 4. Ana Stack Pointer'ı (MSP) uygulamanın değerine ayarla
    // Uygulamanın ilk 4 baytı yığın başlangıç adresidir.
    __asm__ volatile("msr msp, %0" : : "r"(*app_stack_ptr));

    // 5. Uygulamanın Reset Handler'ına zıpla
    app_reset_handler();
}

int main(void) {
    // İleride buraya buton kontrolü ekleyebilirsin:
    // if (gpio_get(GPIOA, GPIO0)) { bootloader_update(); }

    jump_to_main();

    // İşlemci buraya asla ulaşmamalı
    while (1);
    return 0;
}