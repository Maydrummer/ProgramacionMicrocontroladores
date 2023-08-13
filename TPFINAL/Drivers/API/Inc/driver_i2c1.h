/*
 * driver_i2c1.h
 *
 *  Created on: Aug 12, 2023
 *      Author: thony
 */

#ifndef API_INC_DRIVER_I2C1_H_
#define API_INC_DRIVER_I2C1_H_

#include "main.h"
#include "driver_uart.h"


#define scan_address_length     30
#define trial_scan               3
#define timeout_scan            10
#define timeout_transmit       100
#define max_slave              128
#define desplazamiento_7_bits    1
#define one_byte                 1


void gpio_i2c_config(void);
bool_t i2c_init(void);
void scan_address(void);
void transmit_i2c(I2C_HandleTypeDef hi2c,uint16_t address,uint8_t *pstring);


#endif /* API_INC_DRIVER_I2C1_H_ */
