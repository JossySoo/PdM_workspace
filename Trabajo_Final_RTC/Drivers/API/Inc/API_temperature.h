/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/API_temperature.h
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
#ifndef API_TEMPERATURE_H
#define API_TEMPERATURE_H

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
 * @brief  Set the initial state of the state machine.
 * @retval None
 */
void temperatureFSM_init(void);

/**
 * @brief  Check the button state and update the state machine status.
 * @retval None
 */
void temperatureFSM_update(void);

/**
 * @brief  Forces the START_MEASUREMENTS state.
 * @retval None
 */
void temperatureFSM_forceMeasurement(void);


#endif /* API_TEMPERATURE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
