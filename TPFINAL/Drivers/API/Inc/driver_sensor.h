/*
 * driver_sensor.h
 *
 *  Created on: Aug 8, 2023
 *      Author: thony
 */

#ifndef API_INC_DRIVER_SENSOR_H_
#define API_INC_DRIVER_SENSOR_H_

#include "driver_uart.h"

#define frame_length           13 //Longitud de la trama a recibir
#define frame_header_length     4 //Longitud que tiene la sincronizacion de la trama
#define distance_position       5 //Elemento que contiene la informacion de la distancia
#define length_cm_ascii         4 //Longitud de string del valor en cm de la distancia
#define caracter_nulo        '\0' //Caracter nulo en ascii
#define decenas				   10 //Fraccion decenas
#define centenas			  100 //Fraccion centenas
#define cero_ascii            '0' //Caracter cero en ascii

bool_t init_sensor(void); //Funcion donde se obtiene la trama de 13 bytes y valida si es la correcta comparando con el encabezado de 4 bytes
void  get_frame(void); //Funcion que llena el buffer RX del archivo driver_sensor y valida si la trama es correcta
void get_distance(void); //Funcion que extrae la distancia de la trama  y la formateaa en ascii, se llena el buffer donde se alojara en ascii la distancia
void get_distance_error(void); //Funcion que llena el buffer asciiformat con codigo de error "EEE"
uint8_t* return_distance(void); //Funcion que retorna la direccion de memoria de la variable distancia que esta formateada
#endif /* API_INC_DRIVER_SENSOR_H_ */
