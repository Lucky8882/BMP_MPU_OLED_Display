#ifndef BMP280_LL_H
#define BMP280_LL_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

// Write a single byte to a BMP280 register
HAL_StatusTypeDef bmp280_write_reg(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t data);

// Read a single byte from a BMP280 register
HAL_StatusTypeDef bmp280_read_reg(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *data);

// Read multiple bytes from consecutive BMP280 registers
HAL_StatusTypeDef bmp280_read_regs(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len);

#endif // BMP280_LL_H
