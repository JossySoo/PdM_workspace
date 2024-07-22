/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/API_delay.h
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
#ifndef API_DELAY_H
#define API_DELAY_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>  /* Necesaria para uint32_t */
#include <stdbool.h> /* Necesaria para bool y true/false */
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */



/* Exported types ------------------------------------------------------------*/

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct {
    tick_t startTime;
    tick_t duration;
    bool_t running;
} delay_t;

/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
 * @brief  This function initializes the delay, setting the duration but not starting the timer.
 * @param  delay_t * delay, pointer that indicates the delay to initialize
 * @param  duration, duration time of the delay
 * @retval None
 */
void delayInit(delay_t * delay, tick_t duration);

/**
 * @brief  This function starts the delay timer and checks if the duration time has elapsed
 * @param  delay_t * delay, pointer that indicates the delay to check
 * @retval bool timeOut, indicates if the delay time has finished or not
 */
bool_t delayRead(delay_t * delay);

/**
 * @brief  This function modifies the duration time of a delay
 * @param  delay_t * delay, pointer that indicates the delay to modify
 * @retval None
 */
void delayWrite(delay_t * delay, tick_t duration);

/**
 * @brief  This function checks if the delay time has finished or not
 * @param  delay_t * delay, pointer that indicates the delay to modify
 * @retval bool, indicates if the delay time has finished or not
 */
bool_t delayIsRunning(delay_t * delay);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
