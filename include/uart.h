#pragma once
#include "main.h"

extern UART_HandleTypeDef logger_uart;

void uart_init(void);
void log_uart(char*, ...);
