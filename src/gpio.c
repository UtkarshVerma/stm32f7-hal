#include "gpio.h"

void initGPIO() {
	// Initialize PWM GPIO
	PWM_GPIO_CLK_ENABLE();

	GPIO_InitTypeDef pwmStruct = {
		.Pin = PWM_GPIO_PIN,
		.Mode = GPIO_MODE_AF_PP,	   // Alternate function since driven by PWM_TIMER
		.Pull = GPIO_NOPULL,		   // No push-pull config
		.Speed = GPIO_SPEED_FREQ_LOW,  // Go for slow slew rate as we won't switch this pin that fast
		.Alternate = PWM_GPIO_AF,	   // Connect PWM_TIMER to this pin
	};
	HAL_GPIO_Init(PWM_GPIO_PORT, &pwmStruct);
}
