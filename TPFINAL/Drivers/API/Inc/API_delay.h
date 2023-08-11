/*
 * API_delay.h
 *
 *  Created on: 6 jul. 2023
 *      Author: anthony
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_
//Librerias
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "driver_typedef.h"
//Define
#define NULL ((void *)0)

//Prototipo de funciones
void delayInit(delay_t *delay, tick_t duration); //Funcion para cargar el la duracion del retardo
bool_t delayRead(delay_t *delay); //Funcion que verifica el estado del flag running
void delayWrite(delay_t *delay,tick_t duration); //FUncion que  cambia el tiempo de duracion de un delay existente
void Error_t(void);
#endif /* API_INC_API_DELAY_H_ */
