#include "main.h"

void init() {
	HAL_Init();
	initClock();
	initTimers();
	initGPIO();
}

int main() {
	init();

	while (1) {
		PWM_TIMER_CCR = (PWM_TIMER_CCR + 1) % pwmTimerHandle.Init.Period;
		HAL_Delay(1);
	}

	return 0;
}
