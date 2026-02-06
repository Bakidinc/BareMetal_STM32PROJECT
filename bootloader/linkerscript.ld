/*
 * STM32 Nucleo-F410RB Linker Script (Final Fix)
 * STM32F410RBT6 (128KB Flash, 32KB RAM)
 */

MEMORY
{
    rom (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

EXTERN(vector_table)
ENTRY(reset_handler)

SECTIONS
{
    .text : {
        . = ALIGN(4);
        *(.vectors)     /* Vektör tablosu EN BAŞTA */
        . = ALIGN(16);
        
        KEEP (*(.bootloader_section))
        KEEP (*(.firmware_info))
        KEEP (*(.firmware_signature))

        *(.text*)       
        *(.rodata*)
        
        . = ALIGN(4);

        /* --- DÜZELTME BURADA --- */
        /* libopencm3 bu sembolleri arıyor. Onları tanımlı ama boş bırakıyoruz. */
        . = ALIGN(4);
        __preinit_array_start = .;
        __preinit_array_end = .;

        . = ALIGN(4);
        __init_array_start = .;
        __init_array_end = .;

        . = ALIGN(4);
        __fini_array_start = .;
        __fini_array_end = .;
        /* ----------------------- */

        _etext = .;
    } > rom

    .data : {
        _data = .;
        *(.data*)
        *(.ramtext*)
        . = ALIGN(4);
        _edata = .;
    } > ram AT > rom
    _data_loadaddr = LOADADDR(.data);

    .bss : {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > ram

    /* Sadece hata ayıklama bilgilerini atıyoruz */
    /DISCARD/ : {
        *(.eh_frame)
        *(.ARM.exidx*)
        *(.ARM.extab*)
    }

    . = ALIGN(4);
    end = .;
}

PROVIDE(_stack = ORIGIN(ram) + LENGTH(ram));