#include "gpio.h"

void initGPIO() {
	// Initialize blink LED
	LED_PORT_CLK_ENABLE();
	GPIO_InitTypeDef ledStruct = {
		.Pin = LED_PIN,
		.Mode = GPIO_MODE_OUTPUT_PP,
		.Pull = GPIO_PULLUP,
		.Speed = GPIO_SPEED_HIGH};
	HAL_GPIO_Init(LED_PORT, &ledStruct);
}