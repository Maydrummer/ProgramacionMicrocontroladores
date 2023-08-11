/*
 * API_delay.c
 *
 *  Created on: 6 jul. 2023
 *      Author: anthony
 */

#include "API_delay.h"

void delayInit(delay_t *delay, tick_t duration)
{
	if(delay == NULL || duration <= 0)
	{
		Error_t();
	}
	delay->duration=duration; //Se carga la duracion del retador
	delay->running=false; //Iniciamos en false la bandera
}

bool_t delayRead(delay_t *delay)
{
	bool_t temp=false;
	if(delay == NULL)
	{
		Error_t();
	}

	if(delay->running == false)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else if(delay->running == true)
	{
		if(HAL_GetTick() - delay->startTime >= delay->duration)
		{
			delay->running = false; //tiempo cumplido
			temp=true;
		}

	}
	return temp;
}

void delayWrite(delay_t *delay,tick_t duration)
{
	if(delay == NULL || duration <= 0)
	{
		Error_t();
	}
	delay->duration=duration;
}

void Error_t(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	while(1)
	{

	}


  /* USER CODE END Error_Handler_Debug */
}
