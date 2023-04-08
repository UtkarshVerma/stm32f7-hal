#include "gpio.h"

void initGPIO() {
    // Initialize UART logger GPIO
    UARTx_TX_GPIO_CLK_ENABLE();

    GPIO_InitTypeDef logUARTStruct = {
        .Pin   = UARTx_TX_PIN,
        .Mode  = GPIO_MODE_AF_PP,  // Alternate function since driven by USART
        .Pull  = GPIO_NOPULL,      // No push-pull config
        .Speed = GPIO_SPEED_HIGH,  // Go for high slew rate to support higher
                                   // baudrates
        .Alternate = UARTx_TX_AF,  // Connect UART to this pin
    };
    HAL_GPIO_Init(UARTx_TX_GPIO_PORT, &logUARTStruct);

    // Initialize I2C GPIO
    I2Cx_SDA_CLK_ENABLE();
    I2Cx_SCL_CLK_ENABLE();

    GPIO_InitTypeDef i2cGPIO = {
        .Mode  = GPIO_MODE_AF_OD,  // Use alternate function with open-drain
        .Pull  = GPIO_NOPULL,      // Use external pullups
        .Speed = GPIO_SPEED_HIGH,  // Go for high slew rate to support high
                                   // speed transfers
        .Alternate = I2Cx_SCL_SDA_AF,
    };

    i2cGPIO.Pin = I2Cx_SDA_PIN;
    HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &i2cGPIO);

    i2cGPIO.Pin = I2Cx_SCL_PIN;
    HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &i2cGPIO);
}
