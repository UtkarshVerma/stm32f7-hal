#include "gpio.h"

void initGPIO() {
	// Initialize SPI GPIO
	SPI_GPIO_CLK_ENABLE();

	GPIO_InitTypeDef spiGPIO = {
		.Pin = SPI_CS_PIN | SPI_MOSI_PIN | SPI_MISO_PIN | SPI_SCK_PIN,
		.Mode = GPIO_MODE_AF_PP,  // Use alternate function
		.Pull = GPIO_PULLDOWN,
		.Speed = GPIO_SPEED_FREQ_HIGH,	// Go for high slew rate to support high baudrates
		.Alternate = GPIO_AF5_SPI1,		// Enable SPI alternate function
	};

	HAL_GPIO_Init(SPI_GPIO_PORT, &spiGPIO);
}
