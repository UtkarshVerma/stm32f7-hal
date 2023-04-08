#pragma once
#include "main.h"

extern DMA_HandleTypeDef spiTxDMAHandle, spiRxDMAHandle, logUARTDMAHandle;

void initDMA();
