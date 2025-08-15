#include "mpu6500.h"
#include "mpu6500_ll.h"
#include "mpu6500_reg.h"

HAL_StatusTypeDef mpu6500_init(I2C_HandleTypeDef *hi2c) {
    // Wake up device (clear sleep bit)
    return mpu6500_write_reg(hi2c, MPU6500_REG_PWR_MGMT_1, 0x00);
}

HAL_StatusTypeDef mpu6500_set_accel_range(I2C_HandleTypeDef *hi2c, mpu6500_accel_range_t range) {
    uint8_t value = 0;
    switch (range) {
        case MPU6500_ACCEL_2G: value = MPU6500_ACCEL_FS_SEL_2G; break;
        case MPU6500_ACCEL_4G: value = MPU6500_ACCEL_FS_SEL_4G; break;
        case MPU6500_ACCEL_8G: value = MPU6500_ACCEL_FS_SEL_8G; break;
        case MPU6500_ACCEL_16G: value = MPU6500_ACCEL_FS_SEL_16G; break;
        default: value = MPU6500_ACCEL_FS_SEL_2G; break;
    }
    return mpu6500_write_reg(hi2c, MPU6500_REG_ACCEL_CONFIG, value);
}

HAL_StatusTypeDef mpu6500_get_accel_range(I2C_HandleTypeDef *hi2c, mpu6500_accel_range_t *range) {
    uint8_t value;
    if (mpu6500_read_reg(hi2c, MPU6500_REG_ACCEL_CONFIG, &value) != HAL_OK) return HAL_ERROR;
    value &= 0x18;
    switch (value) {
        case MPU6500_ACCEL_FS_SEL_2G: *range = MPU6500_ACCEL_2G; break;
        case MPU6500_ACCEL_FS_SEL_4G: *range = MPU6500_ACCEL_4G; break;
        case MPU6500_ACCEL_FS_SEL_8G: *range = MPU6500_ACCEL_8G; break;
        case MPU6500_ACCEL_FS_SEL_16G: *range = MPU6500_ACCEL_16G; break;
        default: return HAL_ERROR;
    }
    return HAL_OK;
}

HAL_StatusTypeDef mpu6500_set_gyro_range(I2C_HandleTypeDef *hi2c, mpu6500_gyro_range_t range) {
    uint8_t value = 0;
    switch (range) {
        case MPU6500_GYRO_250: value = MPU6500_GYRO_FS_SEL_250; break;
        case MPU6500_GYRO_500: value = MPU6500_GYRO_FS_SEL_500; break;
        case MPU6500_GYRO_1000: value = MPU6500_GYRO_FS_SEL_1000; break;
        case MPU6500_GYRO_2000: value = MPU6500_GYRO_FS_SEL_2000; break;
        default: value = MPU6500_GYRO_FS_SEL_250; break;
    }
    return mpu6500_write_reg(hi2c, MPU6500_REG_GYRO_CONFIG, value);
}

HAL_StatusTypeDef mpu6500_get_gyro_range(I2C_HandleTypeDef *hi2c, mpu6500_gyro_range_t *range) {
    uint8_t value;
    if (mpu6500_read_reg(hi2c, MPU6500_REG_GYRO_CONFIG, &value) != HAL_OK) return HAL_ERROR;
    value &= 0x18;
    switch (value) {
        case MPU6500_GYRO_FS_SEL_250: *range = MPU6500_GYRO_250; break;
        case MPU6500_GYRO_FS_SEL_500: *range = MPU6500_GYRO_500; break;
        case MPU6500_GYRO_FS_SEL_1000: *range = MPU6500_GYRO_1000; break;
        case MPU6500_GYRO_FS_SEL_2000: *range = MPU6500_GYRO_2000; break;
        default: return HAL_ERROR;
    }
    return HAL_OK;
}

HAL_StatusTypeDef mpu6500_read_accel(I2C_HandleTypeDef *hi2c, mpu6500_axis_t *accel) {
    uint8_t data[6];
    if (mpu6500_read_regs(hi2c, MPU6500_REG_ACCEL_XOUT_H, data, 6) != HAL_OK) return HAL_ERROR;
    accel->x = (int16_t)(data[0] << 8 | data[1]);
    accel->y = (int16_t)(data[2] << 8 | data[3]);
    accel->z = (int16_t)(data[4] << 8 | data[5]);
    return HAL_OK;
}

HAL_StatusTypeDef mpu6500_read_gyro(I2C_HandleTypeDef *hi2c, mpu6500_axis_t *gyro) {
    uint8_t data[6];
    if (mpu6500_read_regs(hi2c, MPU6500_REG_GYRO_XOUT_H, data, 6) != HAL_OK) return HAL_ERROR;
    gyro->x = (int16_t)(data[0] << 8 | data[1]);
    gyro->y = (int16_t)(data[2] << 8 | data[3]);
    gyro->z = (int16_t)(data[4] << 8 | data[5]);
    return HAL_OK;
}

HAL_StatusTypeDef mpu6500_get_whoami(I2C_HandleTypeDef *hi2c, uint8_t *whoami) {
    return mpu6500_read_reg(hi2c, MPU6500_REG_WHO_AM_I, whoami);
}
