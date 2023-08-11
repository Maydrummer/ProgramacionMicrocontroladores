/*
 * driver_typedef.h
 *
 *  Created on: Aug 8, 2023
 *      Author: thony
 */

#ifndef API_INC_DRIVER_TYPEDEF_H_
#define API_INC_DRIVER_TYPEDEF_H_
#include <stdbool.h>
#include <stdint.h>

typedef uint32_t tick_t; //Tipo de datos que manejara estructura de retardo no bloqueante
typedef bool bool_t; //Tipo de dato bool redefinido con fines academicos
typedef uint32_t tick_t; //Para el retardo no bloqueante
typedef struct{
	tick_t startTime; //variable que almacenara el tiempo de inicio
	tick_t duration; //variable que almacenara la duració
	bool_t running;  //Variable que almacenara la bandera de si termino el tiempo de espera seteado
}delay_t; //Estructura del rerardo no bloqueante

#endif /* API_INC_DRIVER_TYPEDEF_H_ */
