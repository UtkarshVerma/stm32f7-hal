#pragma once
#include "main.h"

void SysTick_Handler();

void UARTx_TX_DMA_IRQHandler();
void UARTx_IRQHandler();

void SPIx_RX_DMA_IRQHandler();
void SPIx_TX_DMA_IRQHandler();
void SPIx_IRQHandler();
