/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/API_adc.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef API_ADC_H
#define API_ADC_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>  /* Necesaria para uint32_t */
#include <stdbool.h> /* Necesaria para bool y true/false */
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "API_delay.h"



/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
 * @brief  Initializes the ADC peripheral with the specified settings.
 *         Configures the ADC clock, resolution, data alignment, and conversion modes.
 * @param  None
 * @retval None
 */
void adcInit(void);

/**
 * @brief  Polls the ADC for the completion of the conversion.
 *         This function waits until the ADC conversion is complete.
 * @param  None
 * @retval None
 */
void adcPollForConversion (void);

/**
 * @brief  Retrieves the value of the last ADC conversion.
 *         Returns the raw digital value from the ADC conversion.
 * @param  None
 * @retval uint32_t: The raw ADC conversion value.
 */
uint32_t adcGetValue (void);

/**
 * @brief  Transforms the raw ADC value to a temperature value in degrees Celsius.
 *         Converts the raw digital value into a temperature based on the internal
 *         temperature sensor calibration data.
 * @param  rawValue: The raw ADC conversion value.
 * @retval float: The temperature in degrees Celsius.
 */
float adcTransformRawValue (uint32_t rawValue);


#endif /* API_ADC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
