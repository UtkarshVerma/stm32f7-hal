#include "clock.h"

void initClock() {
    RCC_OscInitTypeDef oscillatorStruct = {
        // Enable the 8MHz HSE oscillator
        .OscillatorType = RCC_OSCILLATORTYPE_HSE,
        .HSEState = RCC_HSE_ON,

        // Configure PLL to generate a 216 MHz clock signal using the HSE
        // oscillator
        // PLL = (HSE / m) * n / p
        .PLL =
            {
                .PLLState = RCC_PLL_ON,
                .PLLSource = RCC_PLLSOURCE_HSE,
                .PLLM = 2,
                .PLLN = 108,
                .PLLP = RCC_PLLP_DIV2,
            },
    };
    HAL_RCC_OscConfig(&oscillatorStruct);

    // Activate overdrive to reach the 216 Mhz frequency
    HAL_PWREx_EnableOverDrive();

    // Configure clocks
    RCC_ClkInitTypeDef systemClockStruct = {
        .ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                     RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
        .SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,  // Use PLL clock as the
                                                  // system clock source
        .AHBCLKDivider = RCC_SYSCLK_DIV1,         // AHB = SysClock / 1
        .APB1CLKDivider = RCC_HCLK_DIV4,          // APB1 = AHB / 4
        .APB2CLKDivider = RCC_HCLK_DIV2,          // APB2 = AHB / 2
    };
    HAL_RCC_ClockConfig(&systemClockStruct, FLASH_LATENCY_7);

    // Configure peripheral clocks
    RCC_PeriphCLKInitTypeDef peripheralClockStruct = {
        .PeriphClockSelection = RCC_PERIPHCLK_USART3,
        .Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1,
    };
    HAL_RCCEx_PeriphCLKConfig(&peripheralClockStruct);
}
