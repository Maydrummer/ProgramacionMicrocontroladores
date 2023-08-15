/*
 * driver_sensor_presencia.h
 *
 *  Created on: Aug 15, 2023
 *      Author: thony
 */

#ifndef API_INC_DRIVER_SENSOR_PRESENCIA_H_
#define API_INC_DRIVER_SENSOR_PRESENCIA_H_

#include "driver_typedef.h"
#include "stm32f4xx_hal.h"



void sensor_init(void);
bool_t detectar_presencia(void);


#endif /* API_INC_DRIVER_SENSOR_PRESENCIA_H_ */
