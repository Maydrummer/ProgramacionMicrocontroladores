/*
 * API_uart.h
 *
 *  Created on: Aug 1, 2023
 *      Author: thony
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_
#include "API_typedef.h"
#include "stm32f4xx_hal.h"

bool_t uartInit(); //Inicia la UART e imprime su formato si esta inicio correctamente
void uartSendString(uint8_t *pstring); //Envia caracter por caracter por la uart2 un dato
void uartSendStringSize(uint8_t *pstring, uint16_t size); //Envia x cantidad de caracter de un string, x=size



#endif /* API_INC_API_UART_H_ */
