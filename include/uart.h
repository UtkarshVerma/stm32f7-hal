#pragma once
#include "main.h"

extern UART_HandleTypeDef logUARTHandle;

void initUART();
void logUART(char*, ...);
