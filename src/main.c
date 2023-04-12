#include "main.h"

#include "clock.h"
#include "dma.h"
#include "gpio.h"
#include "spi.h"
#include "uart.h"
#include "util.h"

void init(void) {
    HAL_Init();

    clock_init();
    gpio_init();
    dma_init();
    uart_init();
    spi_init();
}

int main(void) {
    init();

    while (1) {
        log_uart("Listening on SPI\r\n");
        spi_receive(4);
        log_uart("%c %c %c %c\r\n", spi_rx_buffer[0], spi_rx_buffer[1], spi_rx_buffer[2],
                 spi_rx_buffer[3]);
        HAL_Delay(10);
    }

    return 0;
}
