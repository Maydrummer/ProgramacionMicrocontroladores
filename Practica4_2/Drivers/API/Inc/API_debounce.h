/*
 * API_debounce.h
 *
 *  Created on: Jul 25, 2023
 *      Author: thony
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "main.h"
#include "API_delay.h"
//debounce time for FSM
#define t_antirebote 40

// Public functions
void debounceFSM_init();
void debounceFSM_update();


#endif /* API_INC_API_DEBOUNCE_H_ */
