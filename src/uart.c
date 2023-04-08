#include "uart.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "dma.h"

static uint8_t txBuffer[1000];

UART_HandleTypeDef logUARTHandle = {
    .Instance = UARTx,
    .hdmatx   = &logUARTDMAHandle,
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

void initUART() {
    UARTx_CLK_ENABLE();
    HAL_UART_Init(&logUARTHandle);

    // Enable interrupts
    HAL_NVIC_SetPriority(UARTx_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UARTx_IRQn);
}

void logUART(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsprintf((char *)txBuffer, fmt, args);
    va_end(args);

    HAL_UART_Transmit_DMA(&logUARTHandle, txBuffer, strlen((char *)txBuffer));
}
