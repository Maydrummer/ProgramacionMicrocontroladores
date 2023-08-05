/*
 * API_uart.c
 *
 *  Created on: Aug 1, 2023
 *      Author: thony
 */

#include "API_uart.h"

UART_HandleTypeDef huart2;

static bool_t init_status;
static void init_ok(void); //Funcion privada, imprime por por UART2 sus caracteristicas de configuracion
static uint16_t lenString(uint8_t *pointdata);//Funcion privada que retorna el numero de caracteres de un String en formato uin16_t



bool_t uartInit()
{
	init_status=false;
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) == HAL_OK)
	{
		init_status= true;
		init_ok();

	}
	return init_status;
}

static uint16_t lenString(uint8_t *pointdata) //recibe un puntero del string
{
	uint16_t tamano=0; // Inicia con un tamano de cero
	while(*pointdata != '\0') //Se entra al bucle mientras el caracter sea diferente de '\0', que determina final de string
	{
		tamano++; //Se aumenta en 1 el tamano
		pointdata++;//Se aumenta en 1 la direccion del puntero para acceder al otro caracter
	}
	return tamano;//devuelve el tamano del string
}

static void init_ok()
{
	uint8_t cadena1[]= "Modulo USART2 inicializado\n\r";
	uint8_t cadena2[]= "Formato 115200@8N1\n\r";
	uint8_t *p1=cadena1;
	uint8_t *p2=cadena2;
	HAL_UART_Transmit(&huart2, (const uint8_t *)p1,lenString(cadena1), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (const uint8_t *)p2,lenString(cadena2), HAL_MAX_DELAY);
}

void uartSendString(uint8_t *pstring)
{
	while(*pstring)
	{
		HAL_UART_Transmit(&huart2, (const uint8_t *)pstring++,1, HAL_MAX_DELAY);
	}
}

void uartSendStringSize(uint8_t *pstring, uint16_t size)
{
	HAL_UART_Transmit(&huart2, (const uint8_t *)pstring,size, HAL_MAX_DELAY);
}

