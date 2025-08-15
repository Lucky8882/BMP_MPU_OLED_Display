#include "bmp280.h"
#include "bmp280_ll.h"
#include "bmp280_reg.h"

// Helper: Read all calibration registers and fill the struct
static HAL_StatusTypeDef bmp280_read_calib(I2C_HandleTypeDef *hi2c, uint8_t addr, bmp280_calib_t *calib)
{
    uint8_t buf[24];
    // Read 24 bytes of calibration data from 0x88
    if (bmp280_read_regs(hi2c, addr, BMP280_REG_CALIB00, buf, 24) != HAL_OK) return HAL_ERROR;

    // Parse calibration data (see datasheet for order)
    calib->dig_T1 = (uint16_t)(buf[1] << 8 | buf[0]);
    calib->dig_T2 = (int16_t)(buf[3] << 8 | buf[2]);
    calib->dig_T3 = (int16_t)(buf[5] << 8 | buf[4]);
    calib->dig_P1 = (uint16_t)(buf[7] << 8 | buf[6]);
    calib->dig_P2 = (int16_t)(buf[9] << 8 | buf[8]);
    calib->dig_P3 = (int16_t)(buf[11] << 8 | buf[10]);
    calib->dig_P4 = (int16_t)(buf[13] << 8 | buf[12]);
    calib->dig_P5 = (int16_t)(buf[15] << 8 | buf[14]);
    calib->dig_P6 = (int16_t)(buf[17] << 8 | buf[16]);
    calib->dig_P7 = (int16_t)(buf[19] << 8 | buf[18]);
    calib->dig_P8 = (int16_t)(buf[21] << 8 | buf[20]);
    calib->dig_P9 = (int16_t)(buf[23] << 8 | buf[22]);
    return HAL_OK;
}

// Initialize BMP280: check ID, reset, read calibration, set config
HAL_StatusTypeDef bmp280_init(I2C_HandleTypeDef *hi2c, uint8_t addr, bmp280_calib_t *calib)
{
    uint8_t id = 0;
    // Read sensor ID (should be 0x58 for BMP280)
    if (bmp280_read_id(hi2c, addr, &id) != HAL_OK) return HAL_ERROR;
    if (id != 0x58) return HAL_ERROR; // Not a BMP280

    // Soft reset the sensor
    if (bmp280_write_reg(hi2c, addr, BMP280_REG_RESET, 0xB6) != HAL_OK) return HAL_ERROR;
    HAL_Delay(100); // Wait for reset

    // Read calibration data
    if (bmp280_read_calib(hi2c, addr, calib) != HAL_OK) return HAL_ERROR;

    // Set normal mode, temp and pressure oversampling x1, standby 0.5ms, filter off
    if (bmp280_write_reg(hi2c, addr, BMP280_REG_CTRL_MEAS, 0x27) != HAL_OK) return HAL_ERROR;
    if (bmp280_write_reg(hi2c, addr, BMP280_REG_CONFIG, 0x00) != HAL_OK) return HAL_ERROR;

    return HAL_OK;
}

// Read sensor ID (should be 0x58 for BMP280)
HAL_StatusTypeDef bmp280_read_id(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t *id)
{
    return bmp280_read_reg(hi2c, addr, BMP280_REG_ID, id);
}

// Compensation algorithm variables (see datasheet)
static int32_t t_fine;

// Temperature compensation (returns temperature in 0.01 deg C)
static int32_t bmp280_compensate_T(int32_t adc_T, bmp280_calib_t *calib)
{
    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t)calib->dig_T1 << 1))) * ((int32_t)calib->dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)calib->dig_T1)) * ((adc_T >> 4) - ((int32_t)calib->dig_T1))) >> 12) *
            ((int32_t)calib->dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

// Pressure compensation (returns pressure in Pa)
static uint32_t bmp280_compensate_P(int32_t adc_P, bmp280_calib_t *calib)
{
    int64_t var1, var2, p;
    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)calib->dig_P6;
    var2 = var2 + ((var1 * (int64_t)calib->dig_P5) << 17);
    var2 = var2 + (((int64_t)calib->dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)calib->dig_P3) >> 8) + ((var1 * (int64_t)calib->dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)calib->dig_P1) >> 33;
    if (var1 == 0) return 0; // avoid division by zero
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)calib->dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)calib->dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)calib->dig_P7) << 4);
    return (uint32_t)p >> 8;
}

// Read and compensate temperature and pressure
HAL_StatusTypeDef bmp280_read_data(I2C_HandleTypeDef *hi2c, uint8_t addr, bmp280_calib_t *calib, bmp280_data_t *data)
{
    uint8_t buf[6];
    // Read 6 bytes: pressure (3 bytes) + temperature (3 bytes)
    if (bmp280_read_regs(hi2c, addr, BMP280_REG_PRESS_MSB, buf, 6) != HAL_OK) return HAL_ERROR;

    // Assemble raw ADC values (20 bits each, left-aligned in 3 bytes)
    int32_t adc_P = ((uint32_t)buf[0] << 12) | ((uint32_t)buf[1] << 4) | (buf[2] >> 4);
    int32_t adc_T = ((uint32_t)buf[3] << 12) | ((uint32_t)buf[4] << 4) | (buf[5] >> 4);

    // Compensate using calibration data
    data->temperature = bmp280_compensate_T(adc_T, calib); // 0.01 deg C
    data->pressure = bmp280_compensate_P(adc_P, calib);    // Pa

    return HAL_OK;
}
