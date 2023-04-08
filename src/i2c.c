#include "i2c.h"

#define I2Cx_ADDRESS 0xa0

// NOTE: I2C buses are driven through APB1 which is configured to be at 54MHz
// Below are the configurations for driving the bus in fast mode, i.e. 400kHz
// t_SCL ~= (t_SCLH + t_SCLL) * t_I2CCLK
// => t_SCLH = t_SCL / (2 * t_I2CCLK), for a 50% duty cycle
// Refer to section 2.2.2 in AN4235 from ST
#define PRESC  0     // Don't prescale input clock; t_PRESC = t_I2CCLK
#define SCLL   0x34  // Hold SCL LOW for SCLL * t_I2CCLK
#define SCLH   0x44  // Hold SCL HIGH for SCLH * t_I2CCLK
#define SDADEL 0x4   // Data setup time
#define SCLDEL 0x4   // Data setup time

I2C_HandleTypeDef i2cHandle = {
    .Instance = I2Cx,
    .Init =
        {
            .Timing = (PRESC << 28) | (SCLDEL << 20) | (SDADEL << 16) |
                      (SCLH << 8) | SCLL,
            .OwnAddress1     = I2Cx_ADDRESS,
            .AddressingMode  = I2C_ADDRESSINGMODE_7BIT,
            .DualAddressMode = I2C_DUALADDRESS_DISABLE,
            .GeneralCallMode = I2C_GENERALCALL_DISABLE,
            .NoStretchMode   = I2C_NOSTRETCH_DISABLE,  // No clock stretching
        },
};

void i2c_init() {
    I2Cx_CLK_ENABLE();
    HAL_I2C_Init(&i2cHandle);

    // Enable interrupts for I2C
    HAL_NVIC_SetPriority(I2Cx_ER_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(I2Cx_ER_IRQn);
    HAL_NVIC_SetPriority(I2Cx_EV_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(I2Cx_EV_IRQn);
}

int i2c_transmit(byte address, byte* data, word size) {
    if (HAL_I2C_Master_Transmit(&i2cHandle, address << 1, data, size,
                                HAL_MAX_DELAY) != HAL_OK) {
        return 1;
    }

    return 0;
}

int i2c_receive(byte address, byte* buffer, word size) {
    if (HAL_I2C_Master_Receive(&i2cHandle, address << 1, buffer, size,
                               HAL_MAX_DELAY) != HAL_OK) {
        return 1;
    }

    return 0;
}
