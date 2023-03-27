#pragma once
#include <stm32f7xx_hal.h>

#include "clock.h"
#include "crc.h"
#include "gpio.h"
#include "spi.h"
#include "util.h"

#define SPI_INTERFACE SPI1
#define SPI_GPIO_PORT GPIOA
#define SPI_CS_PIN GPIO_PIN_4
#define SPI_SCK_PIN GPIO_PIN_5
#define SPI_MISO_PIN GPIO_PIN_6
#define SPI_MOSI_PIN GPIO_PIN_7
#define SPI_GPIO_AF GPIO_AF5_SPI1
#define SPI_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI_CLK_ENABLE() __HAL_RCC_SPI1_CLK_ENABLE()