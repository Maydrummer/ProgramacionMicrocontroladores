/*
 * driver_sensor.c
 *
 *  Created on: Aug 8, 2023
 *      Author: thony
 *
 *      PA0 UART4 TX
 *      PA1 UART4 RX
 */

#include "driver_sensor.h"

UART_HandleTypeDef huart4;// Se crea estructura para el uart4 donde estara conectado el sensor
extern UART_HandleTypeDef huart2; //Para utilizar la terminar y enviar mensajes de configuracion


//Variables privadas
static bool_t init_status_uart; // Variable que determina si se inicio correctamente el sensor por un booleano
static uint8_t frame_header[frame_header_length]={0x55,0xA5,0x0A,0xD3}; //Trama de sincronizacion
static uint8_t rx_buffer[frame_length];
static uint8_t asciiformat[length_cm_ascii];


/**
  * @brief Funcion que inicia el uart 4 para comunicarse con el sensor tipo radar
  * @note  el formato es 115200@8N1
  * @note  usa la libreria driver_uart.c y envia por el uart2 mensaje de confirmacion de inicio
  * @param ninguno
  * @retval bool_t retorna un boleano, true si se configuro correctamente, caso contrario, false
  */
bool_t init_sensor(void)
{
	init_status_uart=false;
	huart4.Instance = UART4;
	huart4.Init.BaudRate = 115200;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart4) == HAL_OK)
	{
		init_status_uart=true;
		enviar_stringCompleto_uart((uint8_t*)"Sensor inicializado por UART4...\r\n", huart2);
	}
	return init_status_uart;
}


/**
  * @brief Funcion para llenar el buffer de recepcion destinado a distancia del sensor
  * @note  Aqui ya se valida la trama y se extrae distancia
  * @note  Se guarda la distancia en formato ascii en un buffer asciiformat, se usa driver_uart.c
  * @param ninguno
  * @retval ninguno
  */
void  get_frame(void)
{
	bool_t trama_ok;
	clean_rx_buffer(huart4); //Limpiar buffer de recepcion del uart4
	recibir_uart(huart4, rx_buffer, frame_length, HAL_MAX_DELAY); //Recepcion de los 13 bytes
	trama_ok= true; //Antes de entrar al FOR asignamos true a la variable para que si una de la comparacion falla, recibamos un false
	for(uint8_t i=0;i<length_cm_ascii ;i++)
	{
		trama_ok= (rx_buffer[i]==frame_header[i]) && trama_ok;
	}

	if(trama_ok)
	{
		get_distance(); //Llena el buffer ASCII FORMAT con el valor de la distancia leida

	}
	else
	{
		get_distance_error();

	}
}

/**
  * @brief Funcion convierte la distancia en formato ascii
  * @note  Se extrae solo la distancia de la trama recibida
  * @param ninguno
  * @retval ninguno
  */
void get_distance(void)
{
	uint8_t distance;
	uint8_t *ptraux=rx_buffer; //Puntero para acceder al rx_buffer
	ptraux +=distance_position; //Direccion donde se encuentra la distancia en la trama de datos
	distance=*ptraux; //Dato de la distancia
	asciiformat[0]= (distance / centenas) + cero_ascii ;  // Dígito de las centenas
	asciiformat[1]= ((distance / decenas	) % decenas	) + cero_ascii ;  // Dígito de las decenas
	asciiformat[2]= (distance % decenas	) + cero_ascii ; // Dígito de las unidades
	asciiformat[3]= caracter_nulo;  // caracter nulo
}


/**
  * @brief Funcion envia "EEE" en caso de que el encabezado de la trama no sea el correcto
  * @note
  * @param ninguno
  * @retval ninguno
  */
void get_distance_error(void)
{
	uint8_t *ptraux=asciiformat;//Puntero al buffer donde se encuentra formateada la distancia
	for(uint8_t i=0; i< length_cm_ascii; i++)
	{
		*ptraux='E';
		ptraux++;
	}
}

/**
  * @brief Funcion que retorna la direccion de memoria de la cadena asciiformat
  * @note  Esta cadena contiene la distancia en ascii
  * @param ninguno
  * @retval ninguno
  */
uint8_t* return_distance(void)
{
	return asciiformat;
}

