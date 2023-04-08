#pragma once
#include <stm32f7xx_hal.h>

// NOTE: DMA request mappings can be found in tables 27, 28 of RM0410

// UART logger, no need for RX
#define UARTx                      USART3  // Connected to ST-Link
#define UARTx_CLK_ENABLE()         __HAL_RCC_USART3_CLK_ENABLE()
#define UARTx_DMA_CLK_ENABLE()     __HAL_RCC_DMA1_CLK_ENABLE()
#define UARTx_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()

#define UARTx_TX_PIN       GPIO_PIN_8
#define UARTx_TX_GPIO_PORT GPIOD
#define UARTx_TX_AF        GPIO_AF7_USART3

#define UARTx_TX_DMA_STREAM  DMA1_Stream3
#define UARTx_TX_DMA_CHANNEL DMA_CHANNEL_4

#define UARTx_IRQn       USART3_IRQn
#define UARTx_IRQHandler USART3_IRQHandler

#define UARTx_TX_DMA_IRQn       DMA1_Stream3_IRQn
#define UARTx_TX_DMA_IRQHandler DMA1_Stream3_IRQHandler

// I2C bus
#define I2Cx                  I2C1
#define I2Cx_CLK_ENABLE()     __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

#define I2Cx_SCL_PIN       GPIO_PIN_8
#define I2Cx_SCL_GPIO_PORT GPIOB
#define I2Cx_SDA_PIN       GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT GPIOB
#define I2Cx_SCL_SDA_AF    GPIO_AF4_I2C1

#define I2Cx_EV_IRQn       I2C1_EV_IRQn
#define I2Cx_ER_IRQn       I2C1_ER_IRQn
#define I2Cx_EV_IRQHandler I2C1_EV_IRQHandler
#define I2Cx_ER_IRQHandler I2C1_ER_IRQHandler
