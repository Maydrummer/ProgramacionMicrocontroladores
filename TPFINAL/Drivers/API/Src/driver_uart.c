/*
 * driver_uart.c
 *
 *  Created on: Aug 8, 2023
 *      Author: thony
 *      Driver que permite manejo de comunicacion por la uart
 */
#include "driver_uart.h"


void enviar_stringCompleto_uart(uint8_t *pstring,UART_HandleTypeDef huart)
{
	//Envia por la uart string completo
	while(*pstring)
	{
		HAL_UART_Transmit(&huart, (const uint8_t *)pstring++,1, HAL_MAX_DELAY);
	}
}



void enviar_stringcortado_uart(uint8_t *pstring, UART_HandleTypeDef huart,uint16_t size)
{
	//Envia x cantidad de caracter de un string, x=size
	HAL_UART_Transmit(&huart, (const uint8_t *)pstring,size, HAL_MAX_DELAY);
}


void recibir_uart(UART_HandleTypeDef huart,uint8_t *pData,uint16_t size,uint32_t tiempo)
{
	//Recibe datos por la uart y los almacena en el buffer pData
	HAL_UART_Receive(&huart, pData,size, tiempo);
}
