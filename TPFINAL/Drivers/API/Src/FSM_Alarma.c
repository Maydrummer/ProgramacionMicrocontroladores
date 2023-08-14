/*
 * FSM_Alarma.c
 *
 *  Created on: Aug 13, 2023
 *      Author: thony
 */

#include "FSM_Alarma.h"

//DEFINICION DE LA CLAVE

static uint8_t clave[PIN_SIZE + 1]="5656"; //Para asegurar el final de caracter
uint8_t teclado=0;
uint8_t contador=0;
delay_t delay_guarda;
delay_t delay_transition;
typedef enum
{
	DESARMADO_OK,
	ARMANDO,
	ARMADO_OK,
	DESARMANDO,
	INTRUSO,
}fsm_state_t;

delay_t tiempo_guarda_alarma; //Creacion de la estructura del retardo no bloqueante para el tiempo de guarda
static fsm_state_t estado_actual; //Variable que llevara el estado actual de la FSM

//Inicia perifericos necesarios para la aplicacion
void init_perifericos_app(void)
{
	keypad_init();
	while(!(init_terminal()));
	while(!(init_sensor()));
	INIT_LCD();
}

void FSM_init(void)
{
	estado_actual=DESARMADO_OK;
}

void FSM_update(void)
{
	switch(estado_actual)
	{
	case DESARMADO_OK:
		enviar_msg_terminal((uint8_t *)"ESTADO ACTUAL: Desarmado_ok \r\n");
		CLEAR_LCD();
		LCD_XY(LCD_LINEA1,POS_1);
		STRING_LCD((uint8_t *)"Ingrese PIN: ");
		uint8_t contador=0;
		uint8_t clave_ingresada[PIN_SIZE + 1]="";
		uint8_t *ptro_teclado=clave_ingresada;
		uint8_t tecla;
		LCD_XY(LCD_LINEA2,POS_4);
		while(contador < PIN_SIZE)
		{
			tecla=keypad_read();

			if(tecla != '\0')
			{
				*ptro_teclado = tecla;
				contador++;
				ptro_teclado++;
				STRING_LCD((uint8_t *)"*");

			}
		}
		*ptro_teclado= '\0';
		enviar_msg_terminal((uint8_t *)"Clave Ingresada: ");
		enviar_msg_terminal((uint8_t *)clave_ingresada);
		enviar_msg_terminal((uint8_t *)"\r\n");
		if (strcmp((const char *)clave_ingresada,(const char *) clave) == 0)
		{
			enviar_msg_terminal((uint8_t *)"Clave correcta \r\n");
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_1);
			STRING_LCD((uint8_t *)"Clave correcta");
			HAL_Delay(4000);
			estado_actual=ARMANDO;
		}
		else
		{
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_0);
			STRING_LCD((uint8_t *)"Clave incorrecta");
			enviar_msg_terminal((uint8_t *)"Clave Incorrecta \r\n");
			HAL_Delay(4000);
			estado_actual=DESARMADO_OK;
		}
		break;
	case ARMANDO:
		enviar_msg_terminal((uint8_t *)"ARMANDO ALARMA...\r\n");
		CLEAR_LCD();
		LCD_XY(LCD_LINEA1,POS_0);
		STRING_LCD((uint8_t *)"Tiempo de armado: ");
		LCD_XY(LCD_LINEA2,POS_5);
		STRING_LCD((uint8_t *)"15 sec.");
		HAL_Delay(TIEMPO_GUARDA);
		estado_actual=ARMADO_OK;
		enviar_msg_terminal((uint8_t *)"ALARMA ARMADA...\r\n");
		HAL_Delay(TIEMPO_TRANSITION);



		break;
	case ARMADO_OK:
		CLEAR_LCD();
		LCD_XY(LCD_LINEA1,POS_0);
		STRING_LCD((uint8_t *)"Distancia sensor: ");
		enviar_msg_terminal((uint8_t *)"ESTADO ACTUAL: ARMADO_OK \r\n");
		HAL_Delay(500);//Esto no es fijo, solo para pruebas


		break;
	case DESARMANDO:

		break;
	case INTRUSO:

		break;
	default:
		estado_actual=DESARMADO_OK;
		break;
	}
}

