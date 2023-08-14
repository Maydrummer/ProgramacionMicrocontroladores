/*
 * driver_terminal.h
 *
 *  Created on: Aug 12, 2023
 *      Author: thony
 */

#ifndef API_INC_DRIVER_TERMINAL_H_
#define API_INC_DRIVER_TERMINAL_H_
#include "driver_uart.h"



bool_t init_terminal(void);
void enviar_msg_terminal(uint8_t *pstring);



#endif /* API_INC_DRIVER_TERMINAL_H_ */
