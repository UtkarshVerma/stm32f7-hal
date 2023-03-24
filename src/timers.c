#include "timers.h"

// Configure TIM3 for 20 ms period, 8-bit resolution, depending on APB1 timer clock = 108 MHz
// PWM = Timer / ((Prescaler + 1) * (Period + 1))
TIM_HandleTypeDef pwmTimerHandle = {
	.Instance = PWM_TIMER,
	.Init = {
		.Prescaler = 2160 - 1,								  // Scale it down to 108 kHz
		.CounterMode = TIM_COUNTERMODE_UP,					  // Up counter mode
		.Period = 1000 - 1,									  // PWM period in timer ticks for 50 Hz
		.ClockDivision = TIM_CLOCKDIVISION_DIV1,			  // No need of clock division
		.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,  // Period updates can happen anytime
	},
};

void initTimers() {
	// Initialize PWM timer
	PWM_TIMER_CLK_ENABLE();

	if (HAL_TIM_Base_Init(&pwmTimerHandle) != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}

	// Initialize timer with the internal clock source (APB1)
	TIM_ClockConfigTypeDef clockConfig = {
		.ClockSource = TIM_CLOCKSOURCE_INTERNAL,
	};
	if (HAL_TIM_ConfigClockSource(&pwmTimerHandle, &clockConfig) != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}

	if (HAL_TIM_PWM_Init(&pwmTimerHandle) != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}

	// Configure timer as standalone
	TIM_MasterConfigTypeDef masterConfig = {
		.MasterOutputTrigger = TIM_TRGO_RESET,			 // Placebo
		.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE,	 // Disable master-slave mode
	};
	if (HAL_TIMEx_MasterConfigSynchronization(&pwmTimerHandle, &masterConfig) != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}

	// Configure output comparison for the timer
	TIM_OC_InitTypeDef ocConfig = {
		.OCMode = TIM_OCMODE_PWM1,			// Use PWM mode 1, i.e. OCPolarity when count < CCR, and vice versa
		.Pulse = 0,							// Set 0% duty cycle (pulse/period) initially
		.OCPolarity = TIM_OCPOLARITY_HIGH,	// Signal should be HIGH during duty cycle
		.OCFastMode = TIM_OCFAST_DISABLE,	// Disable fast mode
	};
	if (HAL_TIM_PWM_ConfigChannel(&pwmTimerHandle, &ocConfig, TIM_CHANNEL_3) != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}

	if (HAL_TIM_PWM_Start(&pwmTimerHandle, PWM_TIMER_CHANNEL) != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}
}
