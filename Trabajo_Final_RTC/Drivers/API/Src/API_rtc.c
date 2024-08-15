/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/API_rtc.c
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
#include "API_rtc.h"
#include "API_temperature.h"
#include "stm32f4xx_hal_rtc.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_rtc_ex.h"
#include "stm32f4xx_hal_pwr.h"

/* Private Functions ---------------------------------------------------------*/
static void errorHandler(void);

/* Private variables ---------------------------------------------------------*/

/* Global variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* Functions Definitions ------------------------------------------------------*/

void RTC_Init(void) {

    // Configura el RTC
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;


    // Configura el oscilador LSE (Low-Speed External) como fuente de reloj para el RTC
    RCC_OscInitTypeDef RCC_OscInitStruct;

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        	uartSendString((uint8_t*)"Error en RCC_OscConfig\r\n");
        	errorHandler();
    } else {
        	uartSendString((uint8_t*)"RCC_OscConfig correcto\r\n");
    }

    // Selecciona LSE como fuente de reloj para el RTC
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        	uartSendString((uint8_t*)"Error en RCCEx_PeriphCLKConfig\r\n");
        	errorHandler();
    } else {
        	uartSendString((uint8_t*)"RCCEx_PeriphCLKConfig correcto\r\n");
    }

    // Permite el acceso a los registros del RTC
    HAL_PWR_EnableBkUpAccess();
    // Habilita el reloj para el RTC y el Power Controller
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);
    __HAL_RCC_RTC_ENABLE();

    if (HAL_RTC_Init(&hrtc) != HAL_OK) {
        // Inicialización del RTC falló, manejar el error
    	uartSendString((uint8_t*)"Error initializing RTC\r\n");
    	errorHandler();
    } else {
    	uartSendString((uint8_t*)"RTC initialized\r\n");
    }
}

void RTC_WakeUpConfig(uint32_t wakeUpTimeInMs) {
	// Asegurarse de que el Wake-Up Timer esté desactivado
    if (HAL_RTCEx_DeactivateWakeUpTimer(&hrtc) != HAL_OK) {
        uartSendString((uint8_t*)"Error deactivating Wake-Up Timer\r\n");
        errorHandler();
        return;
    }

	// Esperar a que el Wake-Up Timer esté listo para ser configurado
	while (__HAL_RTC_WAKEUPTIMER_GET_FLAG(&hrtc, RTC_FLAG_WUTWF) == RESET) {
	}
	//uartSendString((uint8_t*)"Wake-Up Timer listo\r\n");

    // Convierte milisegundos a segundos (RTC trabaja con segundos)
    uint32_t wakeUpTimeInSec = wakeUpTimeInMs/1000;

    // Configura el Wake-Up Timer del RTC
    if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, wakeUpTimeInSec, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK) {
        // Error al configurar el Wake-Up Timer
    	uartSendString((uint8_t*)"Error configuring Wake-Up Timer\r\n");
    	errorHandler();
    } else {
    	uartSendString((uint8_t*)"Wake-Up Timer configured\r\n");
    }

    HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);

}

void enterLowPowerMode(void) {
    // Suspender el tick del sistema para ahorrar energía
    HAL_SuspendTick();

    uartSendString((uint8_t*)"Entering stop mode ...\r\n");
    // Entra en Stop Mode (modo de bajo consumo)
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFE);

    // Restaurar la configuración del reloj del sistema después de despertar
    SystemClock_Config();

    // Reanudar el tick del sistema
    HAL_ResumeTick();

    uartSendString((uint8_t*)"Se restaura reloj\r\n");
}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc) {
    // Esta función se llama cuando el Wake-Up Timer del RTC expira
    // Cambia el estado de la FSM o realiza otras acciones necesarias
	uartSendString((uint8_t*)"Wake up timer callback\r\n");
	temperatureFSM_forceMeasurement();
}


/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void errorHandler(void){
	/* Turn LED2 on */
	uartSendString((uint8_t*)"RTC error \r\n");
	BSP_LED_On(LED2);
	while (1)
	{
	}
}
