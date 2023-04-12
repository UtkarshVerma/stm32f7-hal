#include "interrupts.h"

#include "dma.h"
#include "uart.h"

void SysTick_Handler(void) { HAL_IncTick(); }

void UARTx_IRQHandler(void) { HAL_UART_IRQHandler(&logger_uart); }

void UARTx_TX_DMA_IRQHandler(void) { HAL_DMA_IRQHandler(&logger_dma); }
