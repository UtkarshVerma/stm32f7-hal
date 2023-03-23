#pragma once
#include <stm32f7xx_hal.h>

#include "clock.h"
#include "gpio.h"
#include "timers.h"
#include "util.h"

#define PWM_GPIO_PIN GPIO_PIN_0
#define PWM_GPIO_PORT GPIOB
#define PWM_GPIO_AF GPIO_AF2_TIM3
#define PWM_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define PWM_TIMER TIM3
#define PWM_TIMER_CHANNEL TIM_CHANNEL_3
#define PWM_TIMER_CCR PWM_TIMER->CCR3
#define PWM_TIMER_CLK_ENABLE() __HAL_RCC_TIM3_CLK_ENABLE()