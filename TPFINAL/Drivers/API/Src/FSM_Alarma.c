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
typedef enum
{
	DESARMADO_OK,
	ARMANDO,
	ARMADO_OK,
	DESARMANDO,
	INTRUSO,
}fsm_state_t;

static fsm_state_t estado_actual; //Variable que llevara el estado actual de la FSM
uint8_t ascii_format[length_tiempo];//Variable para imprimir segundos transcurridos

//Inicia perifericos necesarios para la aplicacion
void init_perifericos_app(void)
{
	keypad_init();
	sensor_init();
	HAL_Delay(100);
	while(!(init_terminal()));
	HAL_Delay(100);
	while(!(init_sensor()));
	HAL_Delay(100);
	INIT_LCD();
	HAL_Delay(100);
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
			uint32_t start_time = HAL_GetTick();//Actualizacion de tiempo
			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
			estado_actual=ARMANDO;

		}
		else
		{
			enviar_msg_terminal((uint8_t *)"Clave Incorrecta \r\n");
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_0);
			STRING_LCD((uint8_t *)"Clave incorrecta");
			uint32_t start_time = HAL_GetTick();//Actualizacion de tiempo
			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
			estado_actual=DESARMADO_OK;
		}
		break;
	case ARMANDO:
		enviar_msg_terminal((uint8_t *)"ARMANDO ALARMA...\r\n");
		CLEAR_LCD();
		for(uint8_t i=0 ; i < TIEMPO_GUARDA; i++)
		{
			uint8_t tiempo_temp=TIEMPO_GUARDA-i; //Actualizacion de la variable i que lleva el numero de iteracion
			int_to_ascii(tiempo_temp,ascii_format);// Conversion a formato ascii
			uint32_t start_time = HAL_GetTick();//Actualizacion de tiempo
			while (HAL_GetTick() - start_time < one_second) {
				LCD_XY(LCD_LINEA1,POS_0);
				STRING_LCD((uint8_t *)"Tiempo de armado: ");
				LCD_XY(LCD_LINEA2,POS_5);
				STRING_LCD((uint8_t *)ascii_format);
			};
		}
		estado_actual=ARMADO_OK;
		uint32_t start_time = HAL_GetTick();//Actualizacion de tiempo
		while (HAL_GetTick() - start_time < TIEMPO_TRANSITION)
		{
			enviar_msg_terminal((uint8_t *)"ALARMA ARMADA...\r\n");
		}
		break;
	case ARMADO_OK:
		enviar_msg_terminal((uint8_t *)"ESTADO ACTUAL: ARMADO_OK \r\n");
		CLEAR_LCD();
		LCD_XY(LCD_LINEA1,POS_0);
		STRING_LCD((uint8_t *)"Alarma ON");
		if(detectar_presencia())
		{
			enviar_msg_terminal((uint8_t *)"Se ha detectado una persona...\r\n");
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_0);
			STRING_LCD((uint8_t *)"PRESENCIA: ON");
			estado_actual=DESARMANDO;
		}
		else
		{
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_0);
			STRING_LCD((uint8_t *)"PRESENCIA: OFF");
		}
		start_time = HAL_GetTick();//Actualizacion de tiempo
		while (HAL_GetTick() - start_time < one_second){};
		break;

	case DESARMANDO:
		start_time= HAL_GetTick();
		while (HAL_GetTick() - start_time < one_second)
		{
			enviar_msg_terminal((uint8_t *)"ALARMA ARMADA...\r\n");
		}
		CLEAR_LCD();
		LCD_XY(LCD_LINEA1,POS_1);
		STRING_LCD((uint8_t *)"Identifiquese: ");
		contador=0;
		uint8_t clave_desbloqueo[PIN_SIZE + 1]="";
		uint8_t *ptro_desbloqueo=clave_desbloqueo;
		uint8_t tecla_desbloqueo;
		LCD_XY(LCD_LINEA2,POS_4);
		while(contador < PIN_SIZE)
		{
			tecla_desbloqueo=keypad_read();

			if(tecla_desbloqueo != '\0')
			{
				*ptro_desbloqueo = tecla_desbloqueo;
				contador++;
				ptro_desbloqueo++;
				STRING_LCD((uint8_t *)"*");

			}
		}
		*ptro_desbloqueo= '\0';
		enviar_msg_terminal((uint8_t *)"Clave Ingresada: ");
		enviar_msg_terminal((uint8_t *)clave_desbloqueo);
		enviar_msg_terminal((uint8_t *)"\r\n");
		if (strcmp((const char *)clave_desbloqueo,(const char *) clave) == 0)
		{
			enviar_msg_terminal((uint8_t *)"Clave correcta \r\n");
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_1);
			STRING_LCD((uint8_t *)"Alarma OFF");
			uint32_t start_time = HAL_GetTick();//Actualizacion de tiempo
			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
			estado_actual=DESARMADO_OK;

		}
		else
		{
			enviar_msg_terminal((uint8_t *)"Clave Incorrecta \r\n");
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_0);
			STRING_LCD((uint8_t *)"INTRUSO");
			uint32_t start_time = HAL_GetTick();//Actualizacion de tiempo
			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
			estado_actual=INTRUSO;
		}


		break;
	case INTRUSO:

		break;
	default:
		estado_actual=DESARMADO_OK;
		break;
	}
}

void int_to_ascii(uint8_t valor,uint8_t *cadena_ascii)
{
	if (valor >= 0 && valor <= 9)
	{
		cadena_ascii[0] = cero_ascii;
		cadena_ascii[1] = cero_ascii + valor; // Carácter de final de cadena
	} else if (valor >= decena && valor <= 15)
	{
		cadena_ascii[0] = '1';
	    cadena_ascii[1] = cero_ascii + (valor - decena);
	}
	cadena_ascii[2]= ' ';
	cadena_ascii[3]= 'S';
	cadena_ascii[4]= 'e';
	cadena_ascii[5]= 'c';
	cadena_ascii[6]= '.';
	cadena_ascii[7]= caracter_final;


}
