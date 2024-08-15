/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/API_uart.h
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
#ifndef __API_UART_H__
#define __API_UART_H__

#include <stdio.h>
#include <stdint.h>  /* Necesaria para uint32_t */
#include <stdbool.h> /* Necesaria para bool y true/false */
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "API_delay.h"

/**
 * Funciones públicas
 */
bool_t uartInit (void);
void uartSendString (uint8_t* pstring);
void uartSendStringSize (uint8_t* pstring, uint16_t size);
void uartReceiveStringSize (uint8_t* pstring, uint16_t size);


#endif /* __API_UART_H__ */
