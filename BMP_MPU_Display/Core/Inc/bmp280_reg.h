#ifndef BMP280_REG_H
#define BMP280_REG_H

// Default I2C address for BMP280 (SDO pin LOW). If SDO is HIGH, use 0x77.
#define BMP280_ADDR             (0x76)

// Register addresses (from BMP280 datasheet)
#define BMP280_REG_ID           0xD0    // Chip ID register
#define BMP280_REG_RESET        0xE0    // Soft reset register
#define BMP280_REG_STATUS       0xF3    // Status register
#define BMP280_REG_CTRL_MEAS    0xF4    // Control (measurement) register
#define BMP280_REG_CONFIG       0xF5    // Configuration register
#define BMP280_REG_PRESS_MSB    0xF7    // Pressure data (MSB)
#define BMP280_REG_TEMP_MSB     0xFA    // Temperature data (MSB)

// Calibration data registers (0x88 to 0xA1)
#define BMP280_REG_CALIB00      0x88
#define BMP280_REG_CALIB25      0xA1

#endif // BMP280_REG_H
