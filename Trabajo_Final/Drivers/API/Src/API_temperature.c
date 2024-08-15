/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/API_temperature.c
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
#include "API_adc.h"
#include "API_temperature.h"

/* Functions -----------------------------------------------------------------*/
static void errorHandler(void);

/* Private define ------------------------------------------------------------*/
#define NUMBER_MEASUREMENTS 5
#define WATING_TIME 5000
/* Private typedef -----------------------------------------------------------*/
typedef enum{
	START_MEASUREMENTS,
	TAKING_MEASUREMENTS,
	AVERAGE_SEND,
	WAITING
} measurementState_t;

/* Private variables ---------------------------------------------------------*/
static measurementState_t measurementState;
static delay_t d1;
static uint8_t countMeasurements;
static float temperatureAccum;
static char msg[50];
static uint16_t rawValue;
static float temp;

/**
 * @brief  Set the initial state of the state machine.
 * @retval None
 */
void temperatureFSM_init(){
	measurementState = START_MEASUREMENTS;
	countMeasurements=0;
	temperatureAccum = 0;
	/* Declare delays and load durations */
	delayInit(&d1, WATING_TIME);
	/* Initialize all configured peripherals */
	uartInit();
	MX_ADC1_Init();
	BSP_LED_Init(LED1);
}

/**
 * @brief  Check the button state and update the state machine status.
 * @retval None
 */
void temperatureFSM_update(){
	switch(measurementState){
		case START_MEASUREMENTS:
			countMeasurements=0;
			temperatureAccum = 0;
			measurementState = TAKING_MEASUREMENTS;
			uartSendString((uint8_t*)"Starting measurements \r\n");
			BSP_LED_On(LED1);
			break;
		case TAKING_MEASUREMENTS:
			if (countMeasurements<NUMBER_MEASUREMENTS){
				adcPollForConversion();
				rawValue = adcGetValue ();
				temp = adcTransformRawValue(rawValue);
				sprintf(msg, "rawValue: %hu\r\n", rawValue);
				uartSendString((uint8_t*) msg);

				// Limitar la precisión a 2 decimales
				sprintf(msg, "Temperature (C): %.2f\r\n", temp);
				uartSendString((uint8_t*) msg);

				countMeasurements +=1;
				temperatureAccum +=temp;
			} else {
				measurementState = AVERAGE_SEND;
			}
			break;
		case AVERAGE_SEND:
			if (countMeasurements==NUMBER_MEASUREMENTS){
				sprintf(msg, "Number of measurements taken: %hu\r\n", NUMBER_MEASUREMENTS);
				uartSendString((uint8_t*) msg);
				temp = temperatureAccum/NUMBER_MEASUREMENTS;
				sprintf(msg, "Average temperature (C): %.2f\r\n", temp);
				uartSendString((uint8_t*) msg);
				BSP_LED_Off(LED1);
				delayRead(&d1);
				uartSendString((uint8_t*)"Starting waiting time ... \r\n");
				measurementState = WAITING;
			} else {
				measurementState = START_MEASUREMENTS;
			}
			break;
		case WAITING:
			if (delayRead(&d1)){
				measurementState = START_MEASUREMENTS;
			}
			break;
		default:
			errorHandler();
			break;
	}
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
