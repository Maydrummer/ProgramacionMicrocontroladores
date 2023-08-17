/*
 * driver_sensor_presencia.c
 *
 *  Created on: Aug 15, 2023
 *      Author: thony
 */


#include "driver_sensor_presencia.h"


/**
  * @brief Funcion que inicializa el GPIO del sensor radar
  * @note
  * @param ninguno
  * @retval ninguno
  */
void sensor_init(void)
{
	GPIO_InitTypeDef gpio_sensor={0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	gpio_sensor.Pin = GPIO_PIN_10;
	gpio_sensor.Mode = GPIO_MODE_INPUT;
	gpio_sensor.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpio_sensor);

}


/**
  * @brief Funcion que retorna un booleano true cuando se detecte movimiento
  * @note
  * @param ninguno
  * @retval bool_t Si es true significa que existio un movimiento
  */
bool_t detectar_presencia(void)
{
	bool_t temp=false;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==GPIO_PIN_SET)
	{
		temp=true;
	}
	return temp;
}


/**
  * @brief Funcion que inicia el GPIO del LED de alarma
  * @note
  * @param ninguno
  * @retval ninguno
  */
void alarma_init_gpio(void)
{
	GPIO_InitTypeDef GPIO_Alarma = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/*Configure GPIO pin : PB3 */
	GPIO_Alarma.Pin = GPIO_PIN_3;
	GPIO_Alarma.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Alarma.Pull = GPIO_NOPULL;
	GPIO_Alarma.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_Alarma);

}

/**
  * @brief Funcion que cambia el estado del GPIOB PIN 3, donde esta mapeado el Led
  * @note
  * @param ninguno
  * @retval ninguno
  */
void alarma_on(void)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
}
