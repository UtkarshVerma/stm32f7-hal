#pragma once
#include "main.h"
#include "util.h"

byte tx_buffer[100], spi_rx_buffer[100];

void spi_init(void);
void spi_receive(word size);
