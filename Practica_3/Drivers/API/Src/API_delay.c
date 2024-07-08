/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/API_delay.c
 * @author  MCD Application Team
 * @brief   This example shows how to retarget the C library printf function
 *          to the UART.
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

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"

/* Functions -----------------------------------------------------------------*/
static void errorHandler(void);
/**
 * @brief  This function initializes the delay, setting the duration but not starting the timer.
 * @param  delay_t * delay, pointer that indicates the delay to initialize
 * @param  duration, duration time of the delay
 * @retval None
 */

void delayInit( delay_t * delay, tick_t duration ) {
	if (delay == NULL || duration<0){
		errorHandler();
	}

	*delay = (delay_t) {
		.startTime = 0,
		.duration = duration,
		.running = false
	};

}

/**
 * @brief  This function starts the delay timer and checks if the duration time has elapsed
 * @param  delay_t * delay, pointer that indicates the delay to check
 * @retval bool timeOut, indicates if the delay time has finished or not
 */

bool_t delayRead( delay_t * delay ) {

	bool_t timeOut = false;

	if (delay == NULL){
		errorHandler();
	}

	if (!(delay->running)) {

		delay->running = true;

		delay->startTime = HAL_GetTick();

	} else {

		if ((HAL_GetTick() - delay->startTime) >= delay->duration) {

			timeOut = true;

			delay->running = false;

		}

	}

	return timeOut;

}

/**
 * @brief  This function modifies the duration time of a delay
 * @param  delay_t * delay, pointer that indicates the delay to modify
 * @retval None
 */

void delayWrite( delay_t * delay, tick_t duration ) {

	if (delay == NULL || duration<0){
			errorHandler();
		}

	delay->duration = duration;

}

/**
 * @brief  This function checks if the delay time has finished or not
 * @param  delay_t * delay, pointer that indicates the delay to modify
 * @retval bool, indicates if the delay time has finished or not
 */

bool_t delayIsRunning(delay_t * delay) {

	if (delay == NULL){
			errorHandler();
		}

	return delay->running;

}


/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void errorHandler(void){
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1)
	{
	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
