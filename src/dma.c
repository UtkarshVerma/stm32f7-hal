#include "dma.h"

#include "uart.h"
#include "util.h"

DMA_HandleTypeDef logger_dma = {
    .Instance = UARTx_TX_DMA_STREAM,
    .Parent   = &logger_uart,
    .Init =
        {
            .Channel             = UARTx_TX_DMA_CHANNEL,
            .Direction           = DMA_MEMORY_TO_PERIPH,
            .PeriphInc           = DMA_PINC_DISABLE,
            .MemInc              = DMA_MINC_ENABLE,
            .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
            .MemDataAlignment    = DMA_MDATAALIGN_BYTE,
            .Mode                = DMA_NORMAL,
            .Priority            = DMA_PRIORITY_LOW,
            .FIFOMode            = DMA_FIFOMODE_DISABLE,
        },
};

void dma_init(void) {
    // Set up DMA for UART logger
    UARTx_DMA_CLK_ENABLE();
    HAL_DMA_Init(&logger_dma);

    // Enable interrupts for UART logger
    HAL_NVIC_SetPriority(UARTx_TX_DMA_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UARTx_TX_DMA_IRQn);
}
