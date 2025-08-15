#include "SSD1306_reg.h"
#include "SSD1306_ll.h"
#include "SSD1306.h"
#include <string.h>

#include "ssd1306_fonts.h"
#include <stdio.h>
#include <stdarg.h>

#define PRINTF_BUF_SIZE 64 // Adjust as needed

// Font parameters
#define FONT6X8_WIDTH 6
#define FONT6X8_HEIGHT 8
#define PRINTF_BUF_SIZE 64
#define MAX_PATTERN_SIZE (PRINTF_BUF_SIZE * (FONT6X8_WIDTH + 1))
extern const uint8_t Font6x8[];

DISPLAY_StatusTypeDef DISPLAY_init(uint8_t i2c_addr)
{
    if (DISPLAY_off(i2c_addr) != DISPLAY_OK) return DISPLAY_ERROR;
    HAL_Delay(10);
    if (DISPLAY_set_clock(i2c_addr) != DISPLAY_OK) return DISPLAY_ERROR;
    HAL_Delay(10);

    uint8_t cmd[] = {SSD1306_CONTROL_CMD, SSD1306_CMD_SET_MULTIPLEX_RATIO, SSD1306_ROWS};
    if (OLED_write(i2c_addr, cmd, sizeof(cmd)) != DISPLAY_OK) return DISPLAY_ERROR;

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_SET_DISPLAY_OFFSET;
    cmd[2] = 0x00;
    if (OLED_write(i2c_addr, cmd, 3) != DISPLAY_OK) return DISPLAY_ERROR;

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_SET_START_LINE;
    cmd[2] = 0x00;
    if (OLED_write(i2c_addr, cmd, 3) != DISPLAY_OK) return DISPLAY_ERROR;

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_CHARGE_PUMP;
    cmd[2] = SSD1306_CHARGE_PUMP_ENABLE;
    if (OLED_write(i2c_addr, cmd, 3) != DISPLAY_OK) return DISPLAY_ERROR;

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_SET_MEMORY_MODE;
    cmd[2] = 0x00;
    if (OLED_write(i2c_addr, cmd, 3) != DISPLAY_OK) return DISPLAY_ERROR;

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_SET_SEG_REMAP_1;
    if (OLED_write(i2c_addr, cmd, 2) != DISPLAY_OK) return DISPLAY_ERROR;

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_COM_SCAN_DIR_DEC;
    if (OLED_write(i2c_addr, cmd, 2) != DISPLAY_OK) return DISPLAY_ERROR;

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_SET_COM_PINS;
    cmd[2] = SSD1306_COM_PINS_128x64;
    if (OLED_write(i2c_addr, cmd, 3) != DISPLAY_OK) return DISPLAY_ERROR;

    if (DISPLAY_set_contrast(i2c_addr, SSD1306_CONTRAST_MEDIUM) != DISPLAY_OK) return DISPLAY_ERROR;
    HAL_Delay(10);

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_SET_PRECHARGE;
    cmd[2] = SSD1306_PRECHARGE_128x64;
    if (OLED_write(i2c_addr, cmd, 3) != DISPLAY_OK) return DISPLAY_ERROR;

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_SET_VCOM_DETECT;
    cmd[2] = SSD1306_VCOMH_086;
    if (OLED_write(i2c_addr, cmd, 3) != DISPLAY_OK) return DISPLAY_ERROR;

    if (DISPLAY_resume(i2c_addr) != DISPLAY_OK) return DISPLAY_ERROR;
    HAL_Delay(10);

    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = SSD1306_CMD_NORMAL_DISPLAY;
    if (OLED_write(i2c_addr, cmd, 2) != DISPLAY_OK) return DISPLAY_ERROR;

    if (DISPLAY_on(i2c_addr) != DISPLAY_OK) return DISPLAY_ERROR;
    HAL_Delay(10);

    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_off(uint8_t i2c_addr)
{
    uint8_t cmd[] = {SSD1306_CONTROL_CMD, SSD1306_CMD_DISPLAY_OFF};
    if (OLED_write(i2c_addr, cmd, sizeof(cmd)) != DISPLAY_OK) return DISPLAY_ERROR;
    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_on(uint8_t i2c_addr)
{
    uint8_t cmd[] = {SSD1306_CONTROL_CMD, SSD1306_CMD_DISPLAY_ON};
    if (OLED_write(i2c_addr, cmd, sizeof(cmd)) != DISPLAY_OK) return DISPLAY_ERROR;
    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_resume(uint8_t i2c_addr)
{
    uint8_t cmd[] = {SSD1306_CONTROL_CMD, SSD1306_CMD_DISPLAY_ALL_ON_RESUME};
    if (OLED_write(i2c_addr, cmd, sizeof(cmd)) != DISPLAY_OK) return DISPLAY_ERROR;
    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_set_clock(uint8_t i2c_addr)
{
    uint8_t cmd[] = {SSD1306_CONTROL_CMD, SSD1306_CMD_SET_DISPLAY_CLOCK_DIV, SSD1306_CLK_OSC8_DIV1};
    if (OLED_write(i2c_addr, cmd, sizeof(cmd)) != DISPLAY_OK) return DISPLAY_ERROR;
    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_set_contrast(uint8_t i2c_addr, SSD1306_Contrast_t value)
{
    uint8_t cmd[] = {SSD1306_CONTROL_CMD, SSD1306_CMD_SET_CONTRAST, value};
    if (OLED_write(i2c_addr, cmd, sizeof(cmd)) != DISPLAY_OK) return DISPLAY_ERROR;
    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_set_page(uint8_t i2c_addr, uint8_t page)
{
    if (page > SSD1306_MAX_PAGE) return DISPLAY_ERROR;
    uint8_t cmd[] = {SSD1306_CONTROL_CMD, (uint8_t)(SSD1306_CMD_SET_PAGE_START | (page & 0x07))};
    if (OLED_write(i2c_addr, cmd, sizeof(cmd)) != DISPLAY_OK) return DISPLAY_ERROR;
    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_set_column(uint8_t i2c_addr, uint8_t column)
{
    if (column > SSD1306_MAX_COLUMN) return DISPLAY_ERROR;
    uint8_t cmd[4];
    cmd[0] = SSD1306_CONTROL_CMD;
    cmd[1] = (uint8_t)(SSD1306_CMD_SET_LOWER_COLUMN | (column & 0x0F));
    cmd[2] = SSD1306_CONTROL_CMD;
    cmd[3] = (uint8_t)(SSD1306_CMD_SET_HIGHER_COLUMN | ((column >> 4) & 0x0F));
    if (OLED_write(i2c_addr, cmd, sizeof(cmd)) != DISPLAY_OK) return DISPLAY_ERROR;
    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_data(uint8_t i2c_addr, uint8_t *data, uint16_t len)
{
    if (data == NULL || len == 0) return DISPLAY_ERROR;
    uint8_t buf[len + 1];
    buf[0] = SSD1306_CONTROL_DATA;
    memcpy(&buf[1], data, len);
    if (OLED_write(i2c_addr, buf, len + 1) != DISPLAY_OK) return DISPLAY_ERROR;
    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_clear(uint8_t i2c_addr)
{
    uint8_t clear[SSD1306_WIDTH] = {0};
    for (uint8_t page = 0; page < SSD1306_PAGES; page++) {
        DISPLAY_set_page(i2c_addr, page);
        DISPLAY_set_column(i2c_addr, 0);
        HAL_Delay(10);
        if (DISPLAY_data(i2c_addr, clear, SSD1306_WIDTH) != DISPLAY_OK) return DISPLAY_ERROR;
    }
    return DISPLAY_OK;
}

DISPLAY_StatusTypeDef DISPLAY_clear_page(uint8_t i2c_addr, uint8_t page)
{
    if (page >= SSD1306_PAGES) return DISPLAY_ERROR;
    uint8_t clear[SSD1306_WIDTH] = {0};
    DISPLAY_set_page(i2c_addr, page);
    DISPLAY_set_column(i2c_addr, 0);
    if (DISPLAY_data(i2c_addr, clear, SSD1306_WIDTH) != DISPLAY_OK) return DISPLAY_ERROR;
    return DISPLAY_OK;
}


//DISPLAY_StatusTypeDef DISPLAY_printf(uint8_t i2c_addr, uint8_t page, uint8_t column, const char *fmt, ...)
//{
//    char buffer[128]; // Enough for one line
//    va_list args;
//    va_start(args, fmt);
//    vsnprintf(buffer, sizeof(buffer), fmt, args);
//    va_end(args);
//
//    DISPLAY_set_page(i2c_addr, page);
//    DISPLAY_set_column(i2c_addr, column);
//
//    for (const char *p = buffer; *p && column < SSD1306_WIDTH; p++) {
//        char c = *p;
//        if (c < 32 || c > 126) c = '?'; // Replace unsupported chars
//
//        uint8_t char_buf[FONT_WIDTH + FONT_SPACING];
//        memcpy(char_buf, font5x8[c - 32], FONT_WIDTH);
//        char_buf[FONT_WIDTH] = 0x00; // spacing
//
//        uint8_t to_write = FONT_WIDTH + FONT_SPACING;
//        if (column + to_write > SSD1306_WIDTH)
//            to_write = SSD1306_WIDTH - column;
//
//        if (DISPLAY_data(i2c_addr, char_buf, to_write) != DISPLAY_OK)
//            return DISPLAY_ERROR;
//
//        column += to_write;
//    }
//    return DISPLAY_OK;
//}


// Helper: Write a single character using your font and API
//void DISPLAY_write_char(uint8_t i2c_addr, uint8_t page, uint8_t *column, char ch) {
//    if (ch < 32 || ch > 126) ch = '?';
//    uint16_t offset = 4 + (ch - 32) * FONT6X8_WIDTH;
//
//    for (uint8_t col = 0; col < FONT6X8_WIDTH; col++) {
//        uint8_t col_data = Font6x8[offset + col];
//        DISPLAY_set_page(i2c_addr, page);
//        DISPLAY_set_column(i2c_addr, *column);
//        DISPLAY_data(i2c_addr, &col_data, 1);
//        (*column)++;
//    }
//    // Add 1 pixel space between characters
//    (*column)++;
//}

DISPLAY_StatusTypeDef DISPLAY_printf(uint8_t i2c_addr, uint8_t page, uint8_t column, const char *fmt, ...) {
    char buf[PRINTF_BUF_SIZE];
    uint8_t pattern[MAX_PATTERN_SIZE];
    size_t pattern_len = 0;

    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    // Build the pattern buffer
    for (size_t i = 0; buf[i] != '\0'; i++) {
        char ch = buf[i];
        if (ch < 32 || ch > 126) ch = '?';
        uint16_t offset = 4 + (ch - 32) * FONT6X8_WIDTH;

        // Copy 6 columns for this character
        for (uint8_t col = 0; col < FONT6X8_WIDTH; col++) {
            if (pattern_len < MAX_PATTERN_SIZE) {
                pattern[pattern_len++] = Font6x8[offset + col];
            }
        }
        // Add 1 pixel space between characters
        if (pattern_len < MAX_PATTERN_SIZE) {
            pattern[pattern_len++] = 0x00;
        }
    }

    // Set page and column once, then send the whole pattern
    DISPLAY_set_page(i2c_addr, page);
    DISPLAY_set_column(i2c_addr, column);
    DISPLAY_data(i2c_addr, pattern, pattern_len);

    return DISPLAY_OK;
}
