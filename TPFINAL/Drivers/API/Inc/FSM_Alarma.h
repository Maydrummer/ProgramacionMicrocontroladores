/*
 * FSM_Alarma.h
 *
 *  Created on: Aug 13, 2023
 *      Author: thony
 */

#ifndef API_INC_FSM_ALARMA_H_
#define API_INC_FSM_ALARMA_H_

#include "driver_typedef.h"
#include "API_delay.h"
#include "driver_lcd.h"
#include "driver_keypad.h"
#include "driver_sensor.h"
#include "driver_terminal.h"


#define TIEMPO_GUARDA           15   //Tiempo de espera de alarma para que el usuario pueda ingresar el pin para desactivar o para que pueda salir luego de activar
#define TIEMPO_TRANSITION     4000   //Tiempo entre transicion
#define one_second            1000
#define PIN_SIZE              4
#define length_tiempo	      7
#define decena                10
#define base_10               'A'
#define cero_ascii            '0'
#define caracter_final        '\0'
void FSM_init(void);
void FSM_update(void);
void init_perifericos_app(void);
void int_to_ascii(uint8_t valor,uint8_t *cadena_ascii);



#endif /* API_INC_FSM_ALARMA_H_ */
