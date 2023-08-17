/*
 * driver_lcd.c
 *
 *  Created on: Aug 12, 2023
 *      Author: thony
 */

#include "driver_lcd.h"

extern I2C_HandleTypeDef hi2c1_t; //Se trae la estructura hi2c1

/**
  * @brief Funcion que inicializa el LCD
  * @note  Se envia los comandos, HOME, MODO DE 4 BITS, POSITION INICIAL Y LIMPIEZA DE LCD
  * @note  Utiliza la libreria driver_i2c
  * @param ninguno
  * @retval ninguno
  */
void INIT_LCD(void)
{
	while(!(i2c_init()));
	CMD_lcd(LCD_HOME);
	CMD_lcd(LCD_4BITS_MODE);
	CMD_lcd(LCD_ON_CMD);
	CMD_lcd(LCD_POSITION0);
	CMD_lcd(LCD_CLEAR);
}

/**
  * @brief Funcion que envia comando de limpieza de LCD
  * @note
  * @param ninguno
  * @retval ninguno
  */
void CLEAR_LCD()
{
	CMD_lcd(LCD_CLEAR);
}


/**
  * @brief Funcion que se encarga de comunicarse con la LCD pero en modo COMANDO
  * @note  Como la comunicacion con la LCD esta seteada por 4 bits, cada byte enviado se envia
  * @note  en 4 partes, se extrae el nibble alto del byte ingresado y el nibble bajo
  * @note  para que la lcd valide los datos se debe enviar cada nibble con un flanco de subida en Enable
  * @note  por esto se hace un OR cada vez que se envie un nibble
  * @param comando recibido en Hexadecimal o entero
  * @retval ninguno
  */
void CMD_lcd(uint8_t comando)
{
  	uint8_t nibble_alto;
  	uint8_t nibble_bajo;
	uint8_t data_transmit[BYTE_SIZE_T];
	nibble_alto= (comando&NIBBLE_MASK); //Extraer nibble alto
	nibble_bajo= ((comando<<BYTE_SIZE_T)&NIBBLE_MASK);//Extraer nibble bajo
	data_transmit[0] = nibble_alto|LCD_ON_CMD;  //en=1, rs=0
	data_transmit[1] = nibble_alto|LCD_OFF_CMD;  //en=0, rs=0
	data_transmit[2] = nibble_bajo|LCD_ON_CMD;  //en=1, rs=0
	data_transmit[3] = nibble_bajo|LCD_OFF_CMD;  //en=0, rs=0
	transmit_i2c(hi2c1_t,SLAVE_ADDRESS_LCD,data_transmit);
	HAL_Delay(1);
}


/**
  * @brief Funcion que se encarga de comunicarse con la LCD pero en modo escritura
  * @note  Como la comunicacion con la LCD esta seteada por 4 bits, cada byte enviado se envia
  * @note  en 4 partes, se extrae el nibble alto del byte ingresado y el nibble bajo
  * @note  para que la lcd valide los datos se debe enviar cada nibble con un flanco de subida en Enable
  * @note  por esto se hace un OR cada vez que se envie un nibble
  * @param comando recibido en Hexadecimal o entero
  * @retval ninguno
  */
void CHAR_LCD(uint8_t caracter)
{
  	uint8_t nibble_alto;
  	uint8_t nibble_bajo;
	uint8_t data_transmit[BYTE_SIZE_T];
	nibble_alto= (caracter&NIBBLE_MASK); //Extraer nibble alto
	nibble_bajo= ((caracter<<BYTE_SIZE_T)&NIBBLE_MASK);//Extraer nibble bajo
	data_transmit[0] = nibble_alto|LCD_ON_CHAR;  //en=1, rs=0
	data_transmit[1] = nibble_alto|LCD_OFF_CHAR;  //en=0, rs=0
	data_transmit[2] = nibble_bajo|LCD_ON_CHAR;  //en=1, rs=0
	data_transmit[3] = nibble_bajo|LCD_OFF_CHAR;  //en=0, rs=0
	transmit_i2c(hi2c1_t,SLAVE_ADDRESS_LCD,data_transmit);
	HAL_Delay(1);

}

/**
  * @brief Funcion que se encarga de escribir en la LCD un string
  * @note  Esta funcion utiliza la funcion CHAR_LCD
  * @note  transmite por i2c con driver_i2c hasta que el puntero del string sea nulo
  * @param *pstring Puntero del string que se ingresa
  * @retval ninguno
  */
void STRING_LCD(uint8_t *pstring)
{
	while (*pstring) CHAR_LCD(*pstring++);
}


/**
  * @brief Funcion que posiciona donde se comenzara a escribir
  * @note  Valida si estamos en la linea 1 o 2
  * @param x este valor representa la fila, 1 o 2
  * @param y este valor representa la columna, va del 0 al 15
  * @retval ninguno
  */
void LCD_XY(uint8_t x,uint8_t y)
{
	if (x == LCD_LINEA1)
	{
		CMD_lcd(LCD_LINEA1|y);
	}
	else if(x == LCD_LINEA2)
	{
		CMD_lcd(LCD_LINEA2|y);
	}
}
