#include "main.h"

void init() {
	HAL_Init();
	initClock();
	initGPIO();
}

int main() {
	init();

	while (1) {
		HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
		HAL_Delay(500);
	}

	return 0;
}
