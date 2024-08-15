/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/API_ADC.c
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

/* Private Functions ---------------------------------------------------------*/
static void errorHandler(void);

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/* Private define ------------------------------------------------------------*/
#define INTERNAL_TEMPSENSOR_AVGSLOPE   ((float)    2.5)	       /* Internal temperature sensor, parameter Avg_Slope (unit: uV/DegCelsius). Refer to device datasheet for min/typ/max values. */
#define INTERNAL_TEMPSENSOR_V25        ((int32_t)  760)        /* Internal temperature sensor, parameter V25 (unit: mV). Refer to device datasheet for min/typ/max values. */
#define INTERNAL_TEMPSENSOR_V25_TEMP   ((int32_t)   25)
#define INTERNAL_TEMPSENSOR_V25_VREF   ((int32_t) 3300)

/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
static ADC_HandleTypeDef adcHandler;

/* Functions Definitions ------------------------------------------------------*/

/**
 * @brief  Initializes the ADC peripheral with the specified settings.
 *         Configures the ADC clock, resolution, data alignment, and conversion modes.
 * @param  None
 * @retval None
 */
void adcInit(void) {
	ADC_ChannelConfTypeDef sConfig;

	/* Enable ADC peripheral */
	__HAL_RCC_ADC1_CLK_ENABLE();

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	adcHandler.Instance = ADC1;
	adcHandler.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	adcHandler.Init.Resolution = ADC_RESOLUTION_12B;
	adcHandler.Init.ScanConvMode = DISABLE;
	adcHandler.Init.ContinuousConvMode = ENABLE;
	adcHandler.Init.DiscontinuousConvMode = DISABLE;
	adcHandler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adcHandler.Init.NbrOfConversion = 1;
	adcHandler.Init.DMAContinuousRequests = DISABLE;
	adcHandler.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	if (HAL_ADC_Init(&adcHandler) != HAL_OK) {
		// Error occurred during ADC initialization
		errorHandler();
	}

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    if (HAL_ADC_ConfigChannel(&adcHandler, &sConfig) != HAL_OK) {
        // Error occurred during ADC channel configuration
    	errorHandler();
    }

    if (HAL_ADC_Start(&adcHandler) != HAL_OK) {
        // Error occurred during ADC start
    	errorHandler();
    }
}

/**
 * @brief  Polls the ADC for the completion of the conversion.
 *         This function waits until the ADC conversion is complete.
 * @param  None
 * @retval None
 */
void adcPollForConversion (void){
	HAL_ADC_PollForConversion(&adcHandler, HAL_MAX_DELAY);
}

/**
 * @brief  Retrieves the value of the last ADC conversion.
 *         Returns the raw digital value from the ADC conversion.
 * @param  None
 * @retval uint32_t: The raw ADC conversion value.
 */
uint32_t adcGetValue (void){
	return HAL_ADC_GetValue(&adcHandler);
}

/**
 * @brief  Transforms the raw ADC value to a temperature value in degrees Celsius.
 *         Converts the raw digital value into a temperature based on the internal
 *         temperature sensor calibration data.
 * @param  rawValue: The raw ADC conversion value.
 * @retval float: The temperature in degrees Celsius.
 */
float adcTransformRawValue (uint32_t rawValue) {
	float temp;

	temp = ((float) rawValue) / 4095 * INTERNAL_TEMPSENSOR_V25_VREF;
	temp = ((temp - INTERNAL_TEMPSENSOR_V25) / INTERNAL_TEMPSENSOR_AVGSLOPE) + INTERNAL_TEMPSENSOR_V25_TEMP;

	return temp;
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void errorHandler(void){
	/* Turn LED2 on */
	uartSendString((uint8_t*)"Adc error \r\n");
	BSP_LED_On(LED2);
	while (1)
	{
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
