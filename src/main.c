#include "main.h"

void init() {
	HAL_Init();
	initClock();
	initGPIO();
	initSPI();
}

int main() {
	init();

	uint8_t outData[] = {0xba, 0xff};
	uint8_t inData[LEN(outData)];

	while (1) {
		HAL_SPI_Transmit(&spiHandle, outData, LEN(outData), HAL_MAX_DELAY);
		HAL_Delay(1000);
	}

	return 0;
}
