#ifndef BMP280_H
#define BMP280_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

// Structure to hold BMP280 calibration data (from datasheet)
typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;
} bmp280_calib_t;

// Structure to hold compensated sensor data
typedef struct {
    int32_t temperature; // in 0.01 deg C (e.g., 2345 = 23.45°C)
    uint32_t pressure;   // in Pa (e.g., 100325 = 1003.25 hPa)
} bmp280_data_t;

// Initialize BMP280, read calibration, set config
HAL_StatusTypeDef bmp280_init(I2C_HandleTypeDef *hi2c, uint8_t addr, bmp280_calib_t *calib);

// Read and compensate temperature and pressure
HAL_StatusTypeDef bmp280_read_data(I2C_HandleTypeDef *hi2c, uint8_t addr, bmp280_calib_t *calib, bmp280_data_t *data);

// Read sensor ID (should be 0x58 for BMP280)
HAL_StatusTypeDef bmp280_read_id(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t *id);

#endif // BMP280_H
