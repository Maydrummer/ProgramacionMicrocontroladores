/*
 * API_debounce.c
 *
 *  Created on: Jul 25, 2023
 *      Author: thony
 */
#include "API_debounce.h"

//Sinonimos de tipos de datos
typedef bool bool_t;

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
}debounceState_t;

//Global private variable
static debounceState_t estado;
delay_t debounce_delay;
//Prototipo funciones
bool_t readKey();

//Desarrollo funciones
bool_t readKey()
{
	static bool_t variable;
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)== GPIO_PIN_RESET) //FLANCO DESCENDENTE
	{
		variable= true;
	}
	else
	{
		variable= false;
	}
	return variable;
}

void debounceFSM_init()
{
	estado= BUTTON_UP;
}

void debounceFSM_update()
{
	switch(estado)
	{
	case BUTTON_UP:
		if(readKey())
		{
			estado= BUTTON_FALLING;
			delayInit(&debounce_delay , t_antirebote);
		}
		break;
	case BUTTON_FALLING:
		if(delayRead(&debounce_delay))
		{
			if(readKey())
			{
				estado= BUTTON_DOWN;
				presionado();
			}
			else
			{
				estado= BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(!(readKey()))
		{
			estado=BUTTON_RAISING;
			delayInit(&debounce_delay , t_antirebote);
		}
		break;
	case BUTTON_RAISING:
		if(delayRead(&debounce_delay))
		{
			if(!(readKey()))
			{
				estado= BUTTON_UP;
				liberado();
			}
			else
			{
				estado= BUTTON_DOWN;
			}
		}
		break;
	default:
		estado= BUTTON_UP;
		break;
	}

}
