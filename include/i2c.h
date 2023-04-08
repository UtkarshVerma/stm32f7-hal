#pragma once
#include "main.h"
#include "util.h"

extern I2C_HandleTypeDef i2cHandle;

void i2c_init();
int i2c_transmit(byte, byte*, word);
int i2c_receive(byte, byte*, word);
