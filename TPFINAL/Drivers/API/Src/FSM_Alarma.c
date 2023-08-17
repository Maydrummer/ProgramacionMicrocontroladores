/*
 * FSM_Alarma.c
 *
 *  Created on: Aug 13, 2023
 *      Author: thony
 */

#include "FSM_Alarma.h"

//DEFINICION DE LA CLAVE

static uint8_t clave[PIN_SIZE + 1]="5656"; //Clave de seguridad del sistema
uint8_t tecla;                             //Variable que almacena el valor actual del teclado
uint8_t contador=0;                        // Variable empleada para validar si se ingreso 4 digitos
uint8_t clave_ingresada[PIN_SIZE + 1]="";  //String que contiene la clave que ingresa el usuario
uint32_t start_time;                       //Variable empleada para los retardos no bloqueantes
static uint32_t tiempo_desarmado;          //Variable que almacenara el tiempo exacto donde se pase al estado de Intruso
										   //Para asi generar un retardo no bloqueante
typedef enum
{
	DESARMADO_OK,
	ARMANDO,
	ARMADO_OK,
	DESARMANDO,
	INTRUSO,
}fsm_state_t;                             // Tipo de dato que almacena los estados de la FSM

static fsm_state_t estado_actual; //Variable que llevara el estado actual de la FSM
uint8_t ascii_format[length_tiempo];//Variable para imprimir segundos transcurridos

/**
  * @brief Funcion que inicia todos los perifericos usados en la aplicacion
  * @note  Se inicia gpio para el teclado, uart para sensor y terminal e I2C para LCD
  * @note
  * @param Ninguno
  * @retval Ninguno
  */
void init_perifericos_app(void)
{
	keypad_init();
	sensor_init();
	alarma_init_gpio();
	HAL_Delay(100);
	while(!(init_terminal()));
	HAL_Delay(100);
	while(!(init_sensor()));
	HAL_Delay(100);
	INIT_LCD();
	HAL_Delay(100);
}

/**
  * @brief Funcion que setea el estado inicial de la FSM
  * @note
  * @note
  * @param Ninguno
  * @retval Ninguno
  */
void FSM_init(void)
{
	estado_actual=DESARMADO_OK;
}

/**
  * @brief Funcion contiene toda la logica de la aplicacion, validando transicion de estados y salidas
  * @note  En esta funcion se utiliza mucho la validacion del pin ingresado por teclado
  * @note
  * @param Ninguno
  * @retval Ninguno
  */

void FSM_update(void)
{
	switch(estado_actual)
	{
	case DESARMADO_OK:
		enviar_msg_terminal((uint8_t *)"ESTADO ACTUAL: Desarmado_ok \r\n");
		CLEAR_LCD();
		LCD_XY(LCD_LINEA1,POS_1);
		STRING_LCD((uint8_t *)"Ingrese PIN: ");
		contador=0;
		uint8_t *ptro_teclado=clave_ingresada;
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
		//Condicion de transicion, si la clave es correcta, se pasa al estado ARMANDO
		if (strcmp((const char *)clave_ingresada,(const char *) clave) == 0)
		{
			enviar_msg_terminal((uint8_t *)"Clave correcta \r\n");
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_1);
			STRING_LCD((uint8_t *)"Clave correcta");
			start_time = HAL_GetTick();//Actualizacion de tiempo
			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
			estado_actual=ARMANDO;

		}
		else
		{
			enviar_msg_terminal((uint8_t *)"Clave Incorrecta \r\n");
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_0);
			STRING_LCD((uint8_t *)"Clave incorrecta");
			start_time = HAL_GetTick();//Actualizacion de tiempo
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
		//Luego del tiempo de guarda se pasa al estado ARMADO_OK
		estado_actual=ARMADO_OK;
		start_time = HAL_GetTick();//Actualizacion de tiempo
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
		//Condicion de transicion es la lectura del sensor de presencia
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
			enviar_msg_terminal((uint8_t *)"Posible Intruso...\r\n");
		}
		CLEAR_LCD();
		LCD_XY(LCD_LINEA1,POS_1);
		STRING_LCD((uint8_t *)"Identifiquese: ");
		contador=0;
		uint8_t *ptro_desbloqueo=clave_ingresada;
		LCD_XY(LCD_LINEA2,POS_4);
		start_time= HAL_GetTick();
		//Si se ingresa correctamente la clave en menos del tiempo de guarda no se activa el estado INTRUSO
		while(contador < PIN_SIZE && (HAL_GetTick() - start_time < TIEMPO_IDENTIFICACION) ) //Condicion donde se valida el tiempo de guarda y si se ingresa PIN correcto
		{
			tecla=keypad_read();

			if(tecla!= '\0')
			{
				*ptro_desbloqueo = tecla;
				contador++;
				ptro_desbloqueo++;
				STRING_LCD((uint8_t *)"*");

			}
		}
		*ptro_desbloqueo= '\0';
		enviar_msg_terminal((uint8_t *)"Clave Ingresada: ");
		enviar_msg_terminal((uint8_t *)clave_ingresada);
		enviar_msg_terminal((uint8_t *)"\r\n");


		if (strcmp((const char *)clave_ingresada,(const char *) clave) == 0)
		{
			enviar_msg_terminal((uint8_t *)"Clave correcta \r\n");
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_1);
			STRING_LCD((uint8_t *)"Alarma OFF");
			start_time = HAL_GetTick();//Actualizacion de tiempo
			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
			estado_actual=DESARMADO_OK;

		}
		else
		{
			enviar_msg_terminal((uint8_t *)"Clave Incorrecta \r\n");
			CLEAR_LCD();
			LCD_XY(LCD_LINEA1,POS_2);
			STRING_LCD((uint8_t *)"INTRUSO!!!");
			start_time = HAL_GetTick();//Actualizacion de tiempo
			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
			estado_actual=INTRUSO;
			tiempo_desarmado= HAL_GetTick();
		}


		break;
	case INTRUSO:
		enviar_msg_terminal((uint8_t *)"Estado Actual: Intruso...\r\n");
		if (HAL_GetTick() - tiempo_desarmado < tiempo_alarma)
		{
			alarma_on();
			HAL_Delay(250);
		}
		else
		{
			enviar_msg_terminal((uint8_t *)"Estado Actual: Volviendo al inicio...\r\n");
			estado_actual=DESARMADO_OK;
		}

		break;
	default:
		estado_actual=DESARMADO_OK;
		break;
	}
}

/**
  * @brief Funcion que convierte un numero entero a cadena de caracteres ascii
  * @note  Esta funcion solo convierte para enteros del 0 al 15
  * @note  Se valida si esta entre el 0 al 9 y si es mayor al 9 y menor a 15
  * @param valor Numero entero sin signo de 8 bits que se quiera representar como ascii
  * @param cadena_ascii Puntero a la cadena_ascii para modificar su contenido
  * @retval Ninguno
  */
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

