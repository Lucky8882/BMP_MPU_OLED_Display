#include "bmp280_ll.h"

// Write a single byte to a BMP280 register
HAL_StatusTypeDef bmp280_write_reg(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t data)
{
    uint8_t buf[2] = {reg, data}; // First byte: register address, second byte: data
    // Send both bytes in one I2C transaction
    return HAL_I2C_Master_Transmit(hi2c, addr << 1, buf, 2, HAL_MAX_DELAY);
}

// Read a single byte from a BMP280 register
HAL_StatusTypeDef bmp280_read_reg(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *data)
{
    HAL_StatusTypeDef status;
    // First, send the register address (write)
    status = HAL_I2C_Master_Transmit(hi2c, addr << 1, &reg, 1, HAL_MAX_DELAY);
    if (status != HAL_OK) return status;
    // Then, read the data from that register (read)
    return HAL_I2C_Master_Receive(hi2c, addr << 1, data, 1, HAL_MAX_DELAY);
}

// Read multiple bytes from consecutive BMP280 registers
HAL_StatusTypeDef bmp280_read_regs(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len)
{
    HAL_StatusTypeDef status;
    // Send the starting register address
    status = HAL_I2C_Master_Transmit(hi2c, addr << 1, &reg, 1, HAL_MAX_DELAY);
    if (status != HAL_OK) return status;
    // Read 'len' bytes starting from that register
    return HAL_I2C_Master_Receive(hi2c, addr << 1, data, len, HAL_MAX_DELAY);
}
