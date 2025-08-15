#ifndef __SSD1306_REG_H
#define __SSD1306_REG_H

// SSD1306 I2C Address (7-bit, shifted left for HAL)
//#define SSD1306_I2C_ADDR         (0x3D << 1) // For STM32 HAL, shift left by 1

// Control bytes
#define SSD1306_CONTROL_CMD      0x00  // Next byte(s) are command(s)
#define SSD1306_CONTROL_DATA     0x40  // Next byte(s) are data

// Display status
typedef enum
{
    DISPLAY_OK       = 0x00U,
    DISPLAY_ERROR    = 0x01U,
    DISPLAY_BUSY     = 0x02U,
    DISPLAY_TIMEOUT  = 0x03U
} DISPLAY_StatusTypeDef;

// Fundamental commands
#define SSD1306_CMD_SET_CONTRAST         0x81
typedef enum {
    SSD1306_CONTRAST_LOW    = 0x7F,
    SSD1306_CONTRAST_MEDIUM = 0xCF,
    SSD1306_CONTRAST_HIGH   = 0xFF
} SSD1306_Contrast_t;

#define SSD1306_CMD_DISPLAY_ALL_ON_RESUME 0xA4
#define SSD1306_CMD_DISPLAY_ALL_ON        0xA5
#define SSD1306_CMD_NORMAL_DISPLAY        0xA6
#define SSD1306_CMD_INVERT_DISPLAY        0xA7
#define SSD1306_CMD_DISPLAY_OFF           0xAE
#define SSD1306_CMD_DISPLAY_ON            0xAF

// Scrolling commands
#define SSD1306_CMD_SCROLL_RIGHT          0x26
#define SSD1306_CMD_SCROLL_LEFT           0x27
#define SSD1306_CMD_SCROLL_VERT_RIGHT     0x29
#define SSD1306_CMD_SCROLL_VERT_LEFT      0x2A
#define SSD1306_CMD_DEACTIVATE_SCROLL     0x2E
#define SSD1306_CMD_ACTIVATE_SCROLL       0x2F
#define SSD1306_CMD_SET_VERTICAL_SCROLL   0xA3

// Addressing setting commands
#define SSD1306_CMD_SET_LOWER_COLUMN      0x00 // 0x00 to 0x0F
#define SSD1306_CMD_SET_HIGHER_COLUMN     0x10 // 0x10 to 0x1F
#define SSD1306_CMD_SET_MEMORY_MODE       0x20
#define SSD1306_CMD_SET_COLUMN_ADDR       0x21
#define SSD1306_CMD_SET_PAGE_ADDR         0x22

// Hardware configuration commands
#define SSD1306_CMD_SET_START_LINE        0x40 // 0x40 to 0x7F
#define SSD1306_CMD_SET_SEG_REMAP_0       0xA0
#define SSD1306_CMD_SET_SEG_REMAP_1       0xA1
#define SSD1306_CMD_SET_MULTIPLEX_RATIO   0xA8
#define SSD1306_CMD_COM_SCAN_DIR_INC      0xC0
#define SSD1306_CMD_COM_SCAN_DIR_DEC      0xC8
#define SSD1306_CMD_SET_DISPLAY_OFFSET    0xD3
#define SSD1306_CMD_SET_COM_PINS          0xDA
typedef enum {
    SSD1306_COM_PINS_128x64 = 0x12,
    SSD1306_COM_PINS_128x32 = 0x02
} SSD1306_ComPins_t;

// Timing & driving scheme
#define SSD1306_CMD_SET_DISPLAY_CLOCK_DIV 0xD5
typedef enum {
    SSD1306_CLK_OSC8_DIV1  = 0x80,
    SSD1306_CLK_OSC8_DIV2  = 0x81,
    SSD1306_CLK_OSC15_DIV1 = 0xF0,
    SSD1306_CLK_OSC1_DIV1  = 0x10
} SSD1306_ClockDivOsc_t;

#define SSD1306_CMD_SET_PRECHARGE         0xD9
typedef enum {
    SSD1306_PRECHARGE_128x64 = 0xF1,
    SSD1306_PRECHARGE_128x32 = 0x22
} SSD1306_Precharge_t;

#define SSD1306_CMD_SET_VCOM_DETECT       0xDB
typedef enum {
    SSD1306_VCOMH_065 = 0x00, // 0.65 x Vcc
    SSD1306_VCOMH_077 = 0x20, // 0.77 x Vcc
    SSD1306_VCOMH_083 = 0x30, // 0.83 x Vcc
    SSD1306_VCOMH_086 = 0x40  // 0.86 x Vcc (default)
} SSD1306_Vcomh_t;

#define SSD1306_CMD_NOP                   0xE3

// Charge pump
#define SSD1306_CMD_CHARGE_PUMP           0x8D
typedef enum {
    SSD1306_CHARGE_PUMP_DISABLE = 0x10, // Disable internal charge pump
    SSD1306_CHARGE_PUMP_ENABLE  = 0x14  // Enable internal charge pump (default for most use)
} SSD1306_ChargePump_t;

// Display dimensions (for 128x64)
#define SSD1306_WIDTH                     128
#define SSD1306_HEIGHT                    64
#define SSD1306_ROWS                      (SSD1306_HEIGHT-1)
#define SSD1306_PAGES                     (SSD1306_HEIGHT / 8)

// Page and column address commands and limits
#define SSD1306_CMD_SET_PAGE_START        0xB0  // Page start address for page addressing mode
#define SSD1306_MAX_PAGE                  7
#define SSD1306_MIN_PAGE                  0

#define SSD1306_MAX_COLUMN                127
#define SSD1306_MIN_COLUMN                0

#endif // __SSD1306_REG_H
