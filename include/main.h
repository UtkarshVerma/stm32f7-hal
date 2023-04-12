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

// SPI bus
#define SPIx                   SPI1
#define SPIx_GPIO_AF           GPIO_AF5_SPI1
#define SPIx_CLK_ENABLE()      __HAL_RCC_SPI1_CLK_ENABLE()
#define SPIx_CS_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_SCK_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MOSI_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MISO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

#define SPIx_CS_PIN         GPIO_PIN_4
#define SPIx_CS_GPIO_PORT   GPIOA
#define SPIx_SCK_PIN        GPIO_PIN_5
#define SPIx_SCK_GPIO_PORT  GPIOA
#define SPIx_MOSI_PIN       GPIO_PIN_7  // NOTE: Remove JP6; UM1974 - Page 63
#define SPIx_MOSI_GPIO_PORT GPIOA
#define SPIx_MISO_PIN       GPIO_PIN_6
#define SPIx_MISO_GPIO_PORT GPIOA
