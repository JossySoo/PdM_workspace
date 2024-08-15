/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/API_rtc.h
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
#ifndef API_RTC_H
#define API_RTC_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>  /* Necesaria para uint32_t */
#include <stdbool.h> /* Necesaria para bool y true/false */
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "API_rcc.h"
#include "API_uart.h"



/* Exported types ------------------------------------------------------------*/



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
 * @brief  This function initializes the RTC peripheral.
 *         It configures the RTC clock source and initializes the RTC with the specified settings.
 * @param  None
 * @retval None
 */
void RTC_Init(void);

/**
 * @brief  This function configures the RTC Wake-Up Timer.
 *         It sets the wake-up time in milliseconds and enables the wake-up interrupt.
 * @param  wakeUpTimeInMs: The wake-up time in milliseconds.
 * @retval None
 */
void RTC_WakeUpConfig(uint32_t wakeUpTimeInMs);

/**
 * @brief  This function puts the microcontroller into Stop Mode to reduce power consumption.
 *         It suspends the system tick, enters Stop Mode, and restores the system clock after waking up.
 * @param  None
 * @retval None
 */
void enterLowPowerMode(void);

/**
 * @brief  This function is executed when the RTC Wake-Up Timer interrupt occurs.
 *         It handles the wake-up event and transitions the FSM to the START_MEASUREMENTS state.
 * @param  hrtc: RTC handle pointer.
 * @retval None
 */
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc);


#endif /* API_RTC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
