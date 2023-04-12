#include "spi.h"

#include "uart.h"

SPI_HandleTypeDef handle = {
    .Instance = SPIx,
    .Init =
        {
            .Mode = SPI_MODE_SLAVE,

            // SPI clock should be scaled down from APB clock
            // NOTE: Keep this value within 2MHz as a thumb rule
            .BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256,

            .Direction = SPI_DIRECTION_2LINES,  // Full-duplex

            // Configure SPI mode 0
            .CLKPhase    = SPI_PHASE_1EDGE,
            .CLKPolarity = SPI_POLARITY_LOW,

            .DataSize       = SPI_DATASIZE_8BIT,
            .FirstBit       = SPI_FIRSTBIT_MSB,
            .TIMode         = SPI_TIMODE_DISABLE,
            .CRCCalculation = SPI_CRCCALCULATION_DISABLE,
            .NSS            = SPI_NSS_HARD_INPUT,  // Use hardware NSS as CS
        },
};

void spi_init(void) {
    SPIx_CLK_ENABLE();
    HAL_SPI_Init(&handle);
}

void spi_receive(word size) {
    if (HAL_SPI_Receive(&handle, spi_rx_buffer, size, HAL_MAX_DELAY) != HAL_OK) {
        log_uart("Receive failed\r\n");
    }
}
