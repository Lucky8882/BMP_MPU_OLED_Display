#include "SSD1306_ll.h"

extern I2C_HandleTypeDef hi2c1;

DISPLAY_StatusTypeDef OLED_write(uint8_t i2c_addr, uint8_t *buf, uint16_t len)
{
    return HAL_I2C_Master_Transmit(&hi2c1, i2c_addr, buf, len, HAL_MAX_DELAY) == HAL_OK ? DISPLAY_OK : DISPLAY_ERROR;
}

DISPLAY_StatusTypeDef OLED_read_reg(uint8_t i2c_addr, uint8_t reg, uint8_t *data)
{
    HAL_StatusTypeDef status;
    status = HAL_I2C_Master_Transmit(&hi2c1, i2c_addr, &reg, 1, HAL_MAX_DELAY);
    if (status != HAL_OK) return DISPLAY_ERROR;
    return HAL_I2C_Master_Receive(&hi2c1, i2c_addr, data, 1, HAL_MAX_DELAY) == HAL_OK ? DISPLAY_OK : DISPLAY_ERROR;
}

DISPLAY_StatusTypeDef OLED_read_regs(uint8_t i2c_addr, uint8_t reg, uint8_t *data, uint16_t len)
{
    HAL_StatusTypeDef status;
    status = HAL_I2C_Master_Transmit(&hi2c1, i2c_addr, &reg, 1, HAL_MAX_DELAY);
    if (status != HAL_OK) return DISPLAY_ERROR;
    return HAL_I2C_Master_Receive(&hi2c1, i2c_addr, data, len, HAL_MAX_DELAY) == HAL_OK ? DISPLAY_OK : DISPLAY_ERROR;
}
