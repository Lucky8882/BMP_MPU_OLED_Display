#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "SSD1306_reg.h"


DISPLAY_StatusTypeDef OLED_write(uint8_t i2c_addr, uint8_t *buf, uint16_t len);

DISPLAY_StatusTypeDef OLED_read_reg(uint8_t i2c_addr, uint8_t reg, uint8_t *data);

DISPLAY_StatusTypeDef OLED_read_regs(uint8_t i2c_addr, uint8_t reg, uint8_t *data, uint16_t len);
