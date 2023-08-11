/*
 * driver_uart.h
 *
 *  Created on: Aug 8, 2023
 *      Author: thony
 */

#ifndef API_INC_DRIVER_UART_H_
#define API_INC_DRIVER_UART_H_
#include "driver_typedef.h"
#include "stm32f4xx_hal.h"

void enviar_stringCompleto_uart(uint8_t *pstring,UART_HandleTypeDef huart); //Envia por la uart string completo
void enviar_stringcortado_uart(uint8_t *pstring, UART_HandleTypeDef huart,uint16_t size); //Envia x cantidad de caracter de un string, x=size
void recibir_uart(UART_HandleTypeDef huart,uint8_t *pData,uint16_t size, uint32_t tiempo); //Recibe datos por la uart y los almacena en el buffer pData


#endif /* API_INC_DRIVER_UART_H_ */
