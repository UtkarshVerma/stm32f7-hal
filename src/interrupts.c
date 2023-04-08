#include "interrupts.h"

#include "dma.h"
#include "i2c.h"
#include "uart.h"

void SysTick_Handler() { HAL_IncTick(); }

// I2C event interrupt request handler
void I2Cx_EV_IRQHandler() { HAL_I2C_EV_IRQHandler(&i2cHandle); }

// I2C error interrupt request handler
void I2Cx_ER_IRQHandler() { HAL_I2C_ER_IRQHandler(&i2cHandle); }

void UARTx_IRQHandler() { HAL_UART_IRQHandler(&logUARTHandle); }

void UARTx_TX_DMA_IRQHandler() { HAL_DMA_IRQHandler(&logUARTDMAHandle); }
