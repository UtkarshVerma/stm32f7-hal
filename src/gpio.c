#include "gpio.h"

void gpio_init(void) {
    // Initialize UART logger GPIO
    UARTx_TX_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef log_uart_gpio = {
        .Pin   = UARTx_TX_PIN,
        .Mode  = GPIO_MODE_AF_PP,  // Alternate function since driven by USART
        .Pull  = GPIO_NOPULL,      // No push-pull config
        .Speed = GPIO_SPEED_HIGH,  // Go for high slew rate to support higher
                                   // baudrates
        .Alternate = UARTx_TX_AF,  // Connect UART to this pin
    };
    HAL_GPIO_Init(UARTx_TX_GPIO_PORT, &log_uart_gpio);

    // Initialize SPI GPIO
    SPIx_CS_CLK_ENABLE();
    SPIx_SCK_CLK_ENABLE();
    SPIx_MOSI_CLK_ENABLE();
    SPIx_MISO_CLK_ENABLE();

    GPIO_InitTypeDef spi_gpio = {
        .Mode  = GPIO_MODE_AF_PP,  // Use alternate function with open-drain
        .Pull  = GPIO_PULLDOWN,    // Use external pullups
        .Speed = GPIO_SPEED_HIGH,  // Go for high slew rate to support high
                                   // speed transfers
        .Alternate = SPIx_GPIO_AF,
    };

    spi_gpio.Pin = SPIx_CS_PIN;
    HAL_GPIO_Init(SPIx_CS_GPIO_PORT, &spi_gpio);

    spi_gpio.Pin = SPIx_SCK_PIN;
    HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &spi_gpio);

    spi_gpio.Pin = SPIx_MOSI_PIN;
    HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &spi_gpio);

    spi_gpio.Pin = SPIx_MISO_PIN;
    HAL_GPIO_Init(SPIx_MISO_GPIO_PORT, &spi_gpio);
}
