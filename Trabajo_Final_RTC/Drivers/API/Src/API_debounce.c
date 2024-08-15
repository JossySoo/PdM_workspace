/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/API_debounce.c
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
#include "API_debounce.h"
#include "API_delay.h"
#include "API_uart.h"

/* Functions -----------------------------------------------------------------*/
static void errorHandler(void);

/* Private define ------------------------------------------------------------*/
#define VALID_BUTTON_TIME 40

/* Private typedef -----------------------------------------------------------*/
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

/* Private variables ---------------------------------------------------------*/
static debounceState_t buttonState;
static delay_t d1;
static bool_t buttonPress;

/**
 * @brief  Set the initial state of the state machine.
 * @retval None
 */
void debounceFSM_init(void){
	buttonState = BUTTON_UP;
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	/* Declare delays and load durations */
	delayInit(&d1, VALID_BUTTON_TIME);
	buttonPress=false;
}

/**
 * @brief  Check the button state and update the state machine status.
 * @retval None
 */
void debounceFSM_update(void){
	switch(buttonState){
		case BUTTON_UP:
			if (BSP_PB_GetState(BUTTON_USER)){
				buttonState = BUTTON_FALLING;
				delayRead(&d1);
			}
			break;
		case BUTTON_DOWN:
			if (!BSP_PB_GetState(BUTTON_USER)){
				buttonState = BUTTON_RAISING;
				delayRead(&d1);
			}
			break;
		case BUTTON_RAISING:
			if (delayRead(&d1)){
				if (!BSP_PB_GetState(BUTTON_USER)){
					buttonState = BUTTON_UP;
					buttonPress=false;
					uartSendString((uint8_t*)"Flanco ascendente detectado \r\n");
				} else {
					buttonState = BUTTON_DOWN;
				}
			}
			break;
		case BUTTON_FALLING:
			if (delayRead(&d1)){
				if (BSP_PB_GetState(BUTTON_USER)){
					buttonState = BUTTON_DOWN;
					buttonPress=true;
					uartSendString((uint8_t*)"Flanco descendente detectado \r\n");
				} else {
					buttonState = BUTTON_UP;
				}
			}
			break;
		default:
			errorHandler();
			break;
	}
}

/**
 * @brief  Check the button state and return true or false if the key was pressed.
 * 			If it returns true, it should reset (set to false) the buttonPress variable.
 * @retval bool timeOut, indicates if the key was pressed.
 */

bool_t debounceFSM_readKey(void){
	if (buttonPress){
		buttonPress=false;
		return true;
	} else {
		return false;
	}

}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void errorHandler(void){
	/* Turn LED2 on */
	uartSendString((uint8_t*)"Debounce error \r\n");
	BSP_LED_On(LED2);
	while (1)
	{
	}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
