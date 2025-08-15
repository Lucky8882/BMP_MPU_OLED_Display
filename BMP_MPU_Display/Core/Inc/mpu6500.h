#ifndef MPU6500_H
#define MPU6500_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef enum {
    MPU6500_ACCEL_2G = 0,
    MPU6500_ACCEL_4G,
    MPU6500_ACCEL_8G,
    MPU6500_ACCEL_16G
} mpu6500_accel_range_t;

typedef enum {
    MPU6500_GYRO_250 = 0,
    MPU6500_GYRO_500,
    MPU6500_GYRO_1000,
    MPU6500_GYRO_2000
} mpu6500_gyro_range_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} mpu6500_axis_t;

typedef struct {
    mpu6500_accel_range_t accel_range;
    mpu6500_gyro_range_t gyro_range;
} mpu6500_config_t;

HAL_StatusTypeDef mpu6500_init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef mpu6500_set_accel_range(I2C_HandleTypeDef *hi2c, mpu6500_accel_range_t range);
HAL_StatusTypeDef mpu6500_get_accel_range(I2C_HandleTypeDef *hi2c, mpu6500_accel_range_t *range);
HAL_StatusTypeDef mpu6500_set_gyro_range(I2C_HandleTypeDef *hi2c, mpu6500_gyro_range_t range);
HAL_StatusTypeDef mpu6500_get_gyro_range(I2C_HandleTypeDef *hi2c, mpu6500_gyro_range_t *range);
HAL_StatusTypeDef mpu6500_read_accel(I2C_HandleTypeDef *hi2c, mpu6500_axis_t *accel);
HAL_StatusTypeDef mpu6500_read_gyro(I2C_HandleTypeDef *hi2c, mpu6500_axis_t *gyro);
HAL_StatusTypeDef mpu6500_get_whoami(I2C_HandleTypeDef *hi2c, uint8_t *whoami);

#endif // MPU6500_H
