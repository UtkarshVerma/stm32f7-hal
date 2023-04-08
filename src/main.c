#include "main.h"

#include "clock.h"
#include "dma.h"
#include "gpio.h"
#include "i2c.h"
#include "uart.h"
#include "util.h"

void init() {
    HAL_Init();
    initClock();

    initGPIO();
    initDMA();
    initUART();
    i2c_init();
}

int main() {
    init();

    const char buffer[] = "Hello!";
    while (1) {
        i2c_transmit(0x7a, (byte*)buffer, LEN(buffer));
        HAL_Delay(1000);
    }

    return 0;
}
