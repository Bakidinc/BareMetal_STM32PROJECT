#include "core/uart.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/usart.h"
#include "libopencm3/cm3/nvic.h"
#include "core/ring-buffer.h"

#define BAUD_RATE 9600
#define RING_BUFFER_SIZE (64)

static ring_buffer_t rb = {0U};

static uint8_t data_buffer[RING_BUFFER_SIZE] = {0U};
static bool data_available =false;

void usart2_isr(void) {
    // 1. Durum: Veri Geldi mi? (RXNE - Read Data Register Not Empty)
    if (usart_get_flag(USART2, USART_FLAG_RXNE)) {
        // Donanımdan veriyi oku (Okuma işlemi otomatik olarak RXNE bayrağını temizler)
        uint8_t data = (uint8_t)usart_recv(USART2);
        
        // Veriyi güvenli bir şekilde arabelleğe yaz
        ring_buffer_write(&rb, data);
    }

    // 2. Durum: Taşma Hatası (ORE - Overrun Error)
    // Bu bayrak set edilirse, veri gelse bile RXNE kalkmaz. Mutlaka temizlenmeli.
    if (usart_get_flag(USART2, USART_FLAG_ORE)) {
        // ORE bayrağını temizlemek için veriyi okumak zorunludur
        (void)usart_recv(USART2); 
    }
}
void uart_setup(void){

    ring_buffer_setup(&rb ,data_buffer,RING_BUFFER_SIZE);
    rcc_periph_clock_enable(RCC_USART2);
    usart_set_flow_control(USART2,USART_FLOWCONTROL_NONE);

    //USARTx Parametreleri 
    usart_set_baudrate(USART2,BAUD_RATE);
    usart_set_databits(USART2,8);
    usart_set_stopbits(USART2,1);
    usart_set_parity(USART2,0);
    usart_set_mode(USART2,USART_MODE_TX_RX);
    usart_enable_rx_interrupt(USART2);
    nvic_enable_irq(NVIC_USART2_IRQ);
    usart_enable(USART2);

}
void uart_write(uint8_t* data ){

while (*data != '\0') {
        usart_send_blocking(USART2, *data);
        data++;
    }
}
void uart_write_byte(uint8_t data){

    usart_send_blocking(USART2,(uint16_t)data);
}
uint32_t uart_read(uint8_t* data, const uint32_t length){

    if(length==0 ){
         
        return 0;
    }
   for (uint32_t bytes_read = 0; bytes_read < length; bytes_read++) {
    if (!ring_buffer_read(&rb, &data[bytes_read])) {
      return bytes_read;
    }
  }
   return length;
    
}
uint8_t uart_read_byte(void){
uint8_t byte=0;

uart_read(&byte,1);

return byte;
}
bool uart_data_available(void){
    return !ring_buffer_empty(&rb);
}