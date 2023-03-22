#pragma once
#include <stm32f7xx_hal.h>

#include "clock.h"
#include "gpio.h"
#include "util.h"

// Blink LED connected to PB0
#define LED_PIN GPIO_PIN_0
#define LED_PORT GPIOB
#define LED_PORT_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()