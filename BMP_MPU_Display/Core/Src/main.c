/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bmp280.h"
#include "bmp280_reg.h"
#include "mpu6500.h"
#include "SSD1306.h"
#include <stdio.h>
#include <stdarg.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DISPLAY1_I2C_ADDR	(0x3D << 1)
#define DISPLAY2_I2C_ADDR	(0x3C << 1)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  bmp280_calib_t calib;   // Calibration data struct
  bmp280_data_t data;     // Sensor data struct

  mpu6500_axis_t accel, gyro;
  HAL_StatusTypeDef mpu_status, bmp_status;
  DISPLAY_StatusTypeDef display1_status, display2_status;

  display1_status = DISPLAY_init(DISPLAY1_I2C_ADDR);
  HAL_Delay(5);
  display2_status = DISPLAY_init(DISPLAY2_I2C_ADDR);
  HAL_Delay(5);
  mpu_status = mpu6500_init(&hi2c1);
  HAL_Delay(5);
  bmp_status = bmp280_init(&hi2c1, BMP280_ADDR, &calib);
  HAL_Delay(5);
  bmp280_write_reg(&hi2c1, BMP280_ADDR, BMP280_REG_CTRL_MEAS, 0x27);
  HAL_Delay(5);
  mpu6500_set_accel_range(&hi2c1, MPU6500_ACCEL_2G);
  HAL_Delay(5);
  mpu6500_set_gyro_range(&hi2c1, MPU6500_GYRO_250);
  HAL_Delay(5);
  mpu6500_read_accel(&hi2c1, &accel);
  HAL_Delay(5);
  mpu6500_read_gyro(&hi2c1, &gyro);
  HAL_Delay(5);
  bmp280_read_data(&hi2c1, BMP280_ADDR, &calib, &data);
  HAL_Delay(5);
  DISPLAY_clear(DISPLAY1_I2C_ADDR);
  HAL_Delay(1);
  DISPLAY_clear(DISPLAY2_I2C_ADDR);
  HAL_Delay(1);
  if(display1_status == DISPLAY_OK && display2_status == DISPLAY_OK){
  if (bmp_status==HAL_OK){
	  DISPLAY_printf(DISPLAY1_I2C_ADDR, 0, 0, "BMP Detected !");
	  HAL_Delay(5);
  }
  if (mpu_status==HAL_OK){
	  DISPLAY_printf(DISPLAY2_I2C_ADDR, 0, 0, "MPU Detected !");
	  HAL_Delay(5);
  }
  }
  DISPLAY_clear(DISPLAY1_I2C_ADDR);
  HAL_Delay(1);
  DISPLAY_clear(DISPLAY2_I2C_ADDR);
  HAL_Delay(1);
  HAL_Delay(100);
  DISPLAY_printf(DISPLAY2_I2C_ADDR, 0, 0, "BMP Measurement");
  HAL_Delay(5);
  DISPLAY_printf(DISPLAY1_I2C_ADDR, 0, 0, "MPU Measurement");
  HAL_Delay(5);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  bmp280_read_data(&hi2c1, BMP280_ADDR, &calib, &data);
	  HAL_Delay(1);
	  DISPLAY_printf(DISPLAY2_I2C_ADDR, 2, 0, "Temperature : %d C",data.temperature/100);
	  HAL_Delay(1);
	  DISPLAY_printf(DISPLAY2_I2C_ADDR, 4, 0, "Pressure : %d hPa",data.pressure/100);
	  HAL_Delay(1);
	  mpu6500_read_accel(&hi2c1, &accel);
	  HAL_Delay(1);
	  mpu6500_read_gyro(&hi2c1, &gyro);
	  HAL_Delay(1);
	  DISPLAY_printf(DISPLAY1_I2C_ADDR, 2, 0, "ACC :");
	  HAL_Delay(1);
	  DISPLAY_printf(DISPLAY1_I2C_ADDR, 4, 2, "X=%d",accel.x);
	  HAL_Delay(1);
	  DISPLAY_printf(DISPLAY1_I2C_ADDR, 5, 2, "Y=%d",accel.y);
	  HAL_Delay(1);
	  DISPLAY_printf(DISPLAY1_I2C_ADDR, 6, 2, "Z=%d",accel.z);
	  HAL_Delay(1);

	  DISPLAY_printf(DISPLAY1_I2C_ADDR, 2, 70, "GYRO :");
	  HAL_Delay(1);
	  DISPLAY_printf(DISPLAY1_I2C_ADDR, 4, 70, "X=%d",gyro.x);
	  HAL_Delay(1);
	  DISPLAY_printf(DISPLAY1_I2C_ADDR, 5, 70, "Y=%d",gyro.y);
	  HAL_Delay(1);
	  DISPLAY_printf(DISPLAY1_I2C_ADDR, 6, 70, "Z=%d",gyro.z);
	  HAL_Delay(50);

//	  DISPLAY_clear_page(DISPLAY1_I2C_ADDR,2);
//	  DISPLAY_clear_page(DISPLAY1_I2C_ADDR,4);
//	  DISPLAY_clear_page(DISPLAY1_I2C_ADDR,5);
//	  DISPLAY_clear_page(DISPLAY1_I2C_ADDR,6);
//
//	  DISPLAY_clear_page(DISPLAY2_I2C_ADDR,2);
//	  DISPLAY_clear_page(DISPLAY2_I2C_ADDR,4);




    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
