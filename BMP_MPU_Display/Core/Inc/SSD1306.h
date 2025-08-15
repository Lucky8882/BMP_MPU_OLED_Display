#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdarg.h>
#include "SSD1306_ll.h"

#define SSD1306_INCLUDE_FONT_6x8
#include "ssd1306_fonts.h"



DISPLAY_StatusTypeDef DISPLAY_init(uint8_t i2c_addr);

DISPLAY_StatusTypeDef DISPLAY_off(uint8_t i2c_addr);
DISPLAY_StatusTypeDef DISPLAY_on(uint8_t i2c_addr);
DISPLAY_StatusTypeDef DISPLAY_resume(uint8_t i2c_addr);
DISPLAY_StatusTypeDef DISPLAY_set_clock(uint8_t i2c_addr);
DISPLAY_StatusTypeDef DISPLAY_set_contrast(uint8_t i2c_addr, SSD1306_Contrast_t value);

DISPLAY_StatusTypeDef DISPLAY_set_page(uint8_t i2c_addr, uint8_t addr);
DISPLAY_StatusTypeDef DISPLAY_set_column(uint8_t i2c_addr, uint8_t column);
DISPLAY_StatusTypeDef DISPLAY_data(uint8_t i2c_addr, uint8_t *data, uint16_t len);
DISPLAY_StatusTypeDef DISPLAY_clear(uint8_t i2c_addr);
DISPLAY_StatusTypeDef DISPLAY_clear_page(uint8_t i2c_addr, uint8_t page);

// Writes a single character at the given page and column, updates column pointer
void DISPLAY_write_char(uint8_t i2c_addr, uint8_t page, uint8_t *column, char ch);
// Prints a formatted string at the given page and column
DISPLAY_StatusTypeDef DISPLAY_printf(uint8_t i2c_addr, uint8_t page, uint8_t column, const char *fmt, ...);

