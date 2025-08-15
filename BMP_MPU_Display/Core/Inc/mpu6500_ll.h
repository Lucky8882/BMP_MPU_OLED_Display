#ifndef MPU6500_LL_H
#define MPU6500_LL_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

HAL_StatusTypeDef mpu6500_write_reg(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t data);
HAL_StatusTypeDef mpu6500_read_reg(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef mpu6500_read_regs(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t *data, uint16_t len);

#endif // MPU6500_LL_H
