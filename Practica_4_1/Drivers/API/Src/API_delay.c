/*
 * API_delay.c
 *
 *  Created on: Jul 4, 2024
 *      Author: felipe
 */

#include "API_delay.h"
#include "main.h"

void delayInit(delay_t* delay, tick_t duration){

	if(delay == NULL){Error_Handler();}

	delay->running = false;
	delay->startTime = 0;
	delay->duration = duration;
}

bool_t delayRead(delay_t* delay){

	if(delay == NULL){Error_Handler();}

	if (delay->running == false){
		delay->startTime = HAL_GetTick();
		delay->running = true;
		return false;
	}

	if ((HAL_GetTick() - delay->startTime) >= delay->duration){
		delay->running = false;
		return true;
	}

	return false;
}

void delayWrite(delay_t* delay, tick_t  duration){

	if(delay == NULL){Error_Handler();}

	delay->duration = duration;
}


