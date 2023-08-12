/*
 * driver_keypad.h
 *
 *  Created on: Aug 11, 2023
 *      Author: thony
 */

#ifndef API_INC_DRIVER_KEYPAD_H_
#define API_INC_DRIVER_KEYPAD_H_

#include "driver_typedef.h"
#include "stm32f4xx_hal.h"
/*
	F1_PIN		//	PB4
	F2_PIN		//	PB5
	F3_PIN		//	PB6
	F4_PIN		//	PB10
	C1_PIN		//	PA6
	C2_PIN		//	PA7
	C3_PIN		//	PA8
	C4_PIN		//	PA9
*/
//Etiquetas que tienen los pines de las filas y columnas
#define F1_Pin GPIO_PIN_4
#define F2_Pin GPIO_PIN_5
#define F3_Pin GPIO_PIN_6
#define F4_Pin GPIO_PIN_10
#define C1_Pin GPIO_PIN_6
#define C2_Pin GPIO_PIN_7
#define C3_Pin GPIO_PIN_8
#define C4_Pin GPIO_PIN_9
#define PORT_F GPIOB
#define PORT_C GPIOA
#define wait_time  20
#define COL1 0
#define COL2 1
#define COL3 2
#define COL4 3
//Estado de pines
#define SET_PIN   GPIO_PIN_SET
#define RESET_PIN GPIO_PIN_RESET
//Filas y columnas
#define n_filas     4
#define n_columnas  4



void keypad_init(void);
uint8_t keypad_read(void);




#endif /* API_INC_DRIVER_KEYPAD_H_ */
