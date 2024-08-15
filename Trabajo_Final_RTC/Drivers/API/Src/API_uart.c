/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/API_uart.c
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
#include "API_uart.h"
#include "stm32f4xx_hal.h"
#include <string.h>

/* Functions -----------------------------------------------------------------*/
static void errorHandler(void);
/* Constants and macros --------------------------------------------------------*/
#define LEN_TMP_MSG 10
#define LEN_INIT_MSG 120
#define NUMERIC_BASE 10

/**
 * Constantes Uart
 */
#define UART_INSTANCE USART3
#define UART_BAUD_RATE 9600
#define UART_WORD_LEN UART_WORDLENGTH_8B
#define UART_STOP_BITS UART_STOPBITS_1
#define UART_PARITY UART_PARITY_NONE

#define MAX_WAIT_UART_TX 500

#define MSG_UART_INIT	"UART iniciada correctamente, boud rate: 9600 \n\r"


/* Variables -----------------------------------------------------------------*/

static UART_HandleTypeDef uartHandle;

static uint8_t msg_uart_init[] = MSG_UART_INIT;

/**
 * @brief Initializes an instance of the UART module
 * @param None
 * @return None
 */
bool_t uartInit (void) {

	bool_t isConfigurationOk = false;

	/* Main config */
	uartHandle.Instance = UART_INSTANCE;
	uartHandle.Init.BaudRate = UART_BAUD_RATE;
	uartHandle.Init.WordLength = UART_WORD_LEN;
	uartHandle.Init.StopBits = UART_STOP_BITS;
	uartHandle.Init.Parity = UART_PARITY;

	uartHandle.Init.Mode = UART_MODE_TX_RX;
	uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	isConfigurationOk = (HAL_UART_Init (&uartHandle) == HAL_OK);

	/*
	 * This message is only sent if the configuration
	 * was successful
	 */
	if (isConfigurationOk) {

		uartSendString(msg_uart_init);

	} else {
		errorHandler();
	}

	return isConfigurationOk;
}


/**
 * @brief Send a character string by serial
 * @param pstring: uint8_t, string to print
 * @return None
 */
void uartSendString (uint8_t* pstring) {

	if (pstring != NULL) {
		//TODO: validar len cuando no hay /0
		uint16_t len = strlen((const char*)pstring);
		//TODO: agregar validacion del return
		HAL_UART_Transmit (&uartHandle, pstring, len, MAX_WAIT_UART_TX);

	} else {
		errorHandler();
	}

}


/**
 * @brief Send a character string by serial
 * @param pstring: uint8_t, string to print
 * @param size: uint16_t, character string length
 * @return None
 */
void uartSendStringSize (uint8_t* pstring, uint16_t size) {
	//TODO: validar size
	if (pstring != NULL) {
		//TODO: agregar validacion del return
		HAL_UART_Transmit (&uartHandle, pstring, size, MAX_WAIT_UART_TX);

	} else {
		errorHandler();
	}

}


/**
 * @brief Receives a string of characters by serial
 * @param pstring: Pointer to the space that stores the received data
 * @param size: uint16_t, character string length
 * @return None
 */
void uartReceiveStringSize (uint8_t* pstring, uint16_t size) {
	//TODO: validar size
	if (pstring != NULL) {
		//TODO: agregar validacion del return
		HAL_UART_Receive (&uartHandle, (uint8_t*)pstring, size, MAX_WAIT_UART_TX);

	} else {
		errorHandler();
	}

}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void errorHandler(void){
	/* Turn LED2 on */
	uartSendString((uint8_t*)"Uart error \r\n");
	BSP_LED_On(LED2);
	while (1)
	{
	}
}
