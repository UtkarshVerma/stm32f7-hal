#include "clock.h"

void initClock() {
	RCC_OscInitTypeDef oscStruct = {
		// Enable the 8MHz HSE oscillator
		.OscillatorType = RCC_OSCILLATORTYPE_HSE,
		.HSEState = RCC_HSE_ON,
		.HSIState = RCC_HSI_OFF,

		// Configure PLL to generate a 216 MHz clock signal using the HSE oscillator
		// PLL = (HSE / m) * n / p
		.PLL = {
			.PLLState = RCC_PLL_ON,
			.PLLSource = RCC_PLLSOURCE_HSE,
			.PLLM = 2,
			.PLLN = 108,
			.PLLP = RCC_PLLP_DIV2,
		},
	};
	if (HAL_RCC_OscConfig(&oscStruct) != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}

	/* Activate the OverDrive to reach the 216 Mhz Frequency */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}

	// Configure clocks
	RCC_ClkInitTypeDef clkStruct = {
		.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
		.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,  // Use PLL clock as the system clock source
		.AHBCLKDivider = RCC_SYSCLK_DIV1,		  // AHB = SysClock / 1
		.APB1CLKDivider = RCC_HCLK_DIV4,		  // APB1 = AHB / 4
		.APB2CLKDivider = RCC_HCLK_DIV2,		  // APB2 = AHB / 2
	};
	if (HAL_RCC_ClockConfig(&clkStruct, FLASH_LATENCY_7) != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}
}

void SysTick_Handler() {
	HAL_IncTick();
}
