#include "main.h"

void init() {
	HAL_Init();
	initClock();
	initTimers();
	initGPIO();
}

int main() {
	init();

	PWM_TIMER_CCR = 0.15 * (pwmTimerHandle.Init.Period + 1);

	while (1)
		;
	return 0;
}
