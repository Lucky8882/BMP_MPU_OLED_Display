#include "mpu6500_ll.h"
#include "mpu6500_reg.h"

HAL_StatusTypeDef mpu6500_write_reg(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t data) {
    return HAL_I2C_Mem_Write(hi2c, MPU6500_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef mpu6500_read_reg(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t *data) {
    return HAL_I2C_Mem_Read(hi2c, MPU6500_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef mpu6500_read_regs(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t *data, uint16_t len) {
    return HAL_I2C_Mem_Read(hi2c, MPU6500_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}
