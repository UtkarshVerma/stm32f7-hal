#include "spi.h"

SPI_HandleTypeDef spiHandle = {
	.Instance = SPI_INTERFACE,
	.Init = {
		.Mode = SPI_MODE_MASTER,
		.Direction = SPI_DIRECTION_2LINES,	// Full duplex
		.DataSize = SPI_DATASIZE_8BIT,
		.CLKPolarity = SPI_POLARITY_LOW,				 // CPOL = 0, clock should idle to LOW
		.CLKPhase = SPI_PHASE_1EDGE,					 // CPHA = 0, sample on leading edge of clock
		.NSS = SPI_NSS_HARD_OUTPUT,						 // Use hardware slave management
		.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256,	 // Scale down APBx accordingly
		.FirstBit = SPI_FIRSTBIT_MSB,
		.TIMode = SPI_TIMODE_DISABLE,
		.CRCCalculation = SPI_CRCCALCULATION_DISABLE,
		.NSSPMode = SPI_NSS_PULSE_ENABLE,  // Pulse CS after transmission
	},
};

void initSPI() {
	SPI_CLK_ENABLE();
	if (HAL_SPI_Init(&spiHandle) != HAL_OK) {
		errorHandler(__FILE__, __LINE__);
	}
}
