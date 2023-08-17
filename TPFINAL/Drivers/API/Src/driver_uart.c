/*
 * driver_uart.c
 *
 *  Created on: Aug 8, 2023
 *      Author: thony
 *      Driver que permite manejo de comunicacion por la uart
 */
#include "driver_uart.h"


/**
  * @brief Funcion que envia por uart un string
  * @note  el while valida que mientras no sea un caracter nulo, se transmita por uart
  * @note  Se transmite un caracter a la vez, al final se limpia el buffer de transmision
  * @param *pstring Puntero al string que queramos transmitir
  * @param huart Estructura del uart que vayamos a utilizar
  * @retval Ninguno
  */
void enviar_stringCompleto_uart(uint8_t *pstring,UART_HandleTypeDef huart)
{
	//Envia por la uart string completo
	while(*pstring)
	{
		HAL_UART_Transmit(&huart, (const uint8_t *)pstring++,1, HAL_MAX_DELAY);
	}
	HAL_UART_AbortTransmit(&huart);
}

/**
  * @brief Funcion que envia por uart una cantidad especifica de caracteres de un string
  * @note  Utiiza la libreria uart de la HAL
  * @param *pstring Puntero al string que queramos transmitir
  * @param huart Estructura del uart que vayamos a utilizar
  * @param size valor entero de 16 bits que indica cuantos caracteres se van a transmitir
  * @retval Ninguno
  */

void enviar_stringcortado_uart(uint8_t *pstring, UART_HandleTypeDef huart,uint16_t size)
{
	//Envia x cantidad de caracter de un string, x=size
	HAL_UART_Transmit(&huart, (const uint8_t *)pstring,size, HAL_MAX_DELAY);
}

/**
  * @brief Funcion que recibe por uart un string
  * @note  Se le puede especificar el tamano del dato
  * @note  usa la HAL
  * @param huart Estructura del uart que vayamos a utilizar
  * @param *pData puntero al buffer de recepcion
  * @param size tamano del dato a recibir
  * @param tiempo el timeout
  * @retval Ninguno
  */

void recibir_uart(UART_HandleTypeDef huart,uint8_t *pData,uint16_t size,uint32_t tiempo)
{
	//Recibe datos por la uart y los almacena en el buffer pData
	HAL_UART_Receive(&huart, pData,size, tiempo);
}

/**
  * @brief Funcion que limpia el buffer de recepcion de la UART
  * @note  usa la HAL
  * @param huart Estructura del uart que vayamos a utilizar
  * @retval Ninguno
  */
void clean_rx_buffer(UART_HandleTypeDef huart)
{
	HAL_UART_AbortReceive(&huart);
}

/**
  * @brief Funcion que limpia el buffer de transmision de la UART
  * @note  usa la HAL
  * @param huart Estructura del uart que vayamos a utilizar
  * @retval Ninguno
  */
void clean_tx_buffer(UART_HandleTypeDef huart)
{
	HAL_UART_AbortTransmit(&huart);

}
