/**
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
#include "main.h"
#include <string.h>
#include "API_delay.h"
#include "API_debounce.h"
#include "API_uart.h"
#include "API_adc.h"
#include "API_temperature.h"
#include "API_rcc.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef uartHandle;


/* Private function prototypes -----------------------------------------------*/

static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/


/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {
	/* STM32F4xx HAL library initialization:
	 - Configure the Flash prefetch
	 - Systick timer is configured by default as source of time base, but user
	 can eventually implement his proper time base source (a general purpose
	 timer for example or other time source), keeping in mind that Time base
	 duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
	 handled in milliseconds basis.
	 - Set NVIC Group Priority to 4
	 - Low Level Initialization
	 */
	HAL_Init();

	//Nucleo_BSP_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP Led for LED2 and LED3*/
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	/* Initialize required modules*/
	debounceFSM_init();
	temperatureFSM_init();
	debounceFSM_init();

	/* Infinite loop */
	while (1) {
		temperatureFSM_update();
		debounceFSM_update();
		if (debounceFSM_readKey()){
			temperatureFSM_forceMeasurement();
		}

	}
}


/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
	/* Turn LED2 on */
	uartSendString((uint8_t*)"Main error \r\n");
	BSP_LED_On(LED2);
	while (1) {
	}
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif
