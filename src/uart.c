#include "uart.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "dma.h"

static uint8_t tx_buffer[1000];

UART_HandleTypeDef logger_uart = {
    .Instance = UARTx,
    .hdmatx   = &logger_dma,
    .Init =
        {
            .BaudRate   = 115200,
            .WordLength = UART_WORDLENGTH_8B,
            .StopBits   = UART_STOPBITS_1,
            .Parity     = UART_PARITY_NONE,

            .Mode      = UART_MODE_TX,         // Block incoming traffic
            .HwFlowCtl = UART_HWCONTROL_NONE,  // No need of flow control
        },
};

void uart_init(void) {
    UARTx_CLK_ENABLE();
    HAL_UART_Init(&logger_uart);

    // Enable interrupts
    HAL_NVIC_SetPriority(UARTx_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UARTx_IRQn);
}

void log_uart(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsprintf((char *)tx_buffer, fmt, args);
    va_end(args);

    HAL_UART_Transmit_DMA(&logger_uart, tx_buffer, strlen((char *)tx_buffer));
}
