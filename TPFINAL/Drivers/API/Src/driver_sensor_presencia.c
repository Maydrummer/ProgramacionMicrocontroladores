/*
 * driver_sensor_presencia.c
 *
 *  Created on: Aug 15, 2023
 *      Author: thony
 */

//Funcion que activa el gpio PA10 para lecturar la presencia
#include "driver_sensor_presencia.h"

void sensor_init(void)
{
	GPIO_InitTypeDef gpio_sensor={0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	gpio_sensor.Pin = GPIO_PIN_10;
	gpio_sensor.Mode = GPIO_MODE_INPUT;
	gpio_sensor.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpio_sensor);

}


//Basicamente devuelve un true cuando se detecta presencia
bool_t detectar_presencia(void)
{
	bool_t temp=false;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==GPIO_PIN_SET)
	{
		temp=true;
	}
	return temp;
}
