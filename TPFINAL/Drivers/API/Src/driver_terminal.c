/*
 * driver_terminal.c
 *
 *  Created on: Aug 12, 2023
 *      Author: thony
 */
#include "driver_terminal.h"

UART_HandleTypeDef huart2;

bool_t init_terminal(void)
{
	bool_t state_uart=false;
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
		state_uart=true;
		enviar_stringCompleto_uart((uint8_t*)"Terminal por UART2 lista...\r\n", huart2);
	}
	return state_uart;
}

