/*
 * driver_lcd.h
 *
 *  Created on: Aug 12, 2023
 *      Author: thony
 */

#ifndef API_INC_DRIVER_LCD_H_
#define API_INC_DRIVER_LCD_H_

#include "driver_i2c1.h"

//Comandos LCD en Hexadecimal
#define     LCD_CLEAR	    0x01    //Limpiar pantalla
#define     LCD_HOME	    0x02    //Retorno al inicio
#define     LCD_POSITION0   0x80    //Comando para empezar a definir una posicion 80+ (1 al 32) ya que es LCD 16*2
#define     LCD_4BITS_MODE  0x28    //Modo 4 bits 2 filas
#define     LCD_LINEA1	    0x80	//Primera Fila
#define     LCD_LEFT		0x10	//Cursor a la izquierda
#define     LCD_LINEA2		0XC0	//Segunda Fila
#define     LCD_OFF 		0x08	//Apagar el display
#define     LCD_ON_CMD      0x0C    //Para validar dato transmitido
#define     LCD_OFF_CMD 	0x08    //Para hacer un flanco en la habilitacion del dato
#define     LCD_ON_CHAR     0x0D    //Para validar envio de dato en pantalla
#define     LCD_OFF_CHAR    0x09	//Para hacer un flanco previo al envio de otro caracter en pantalla
#define     BYTE_SIZE_T		   4    //Tamano fijo de transmision
#define     NIBBLE_MASK		0xF0	//Para enmascarar el nibble alto
//Posicion en lcd
#define     POS_0           0x00
#define     POS_1           0x01
#define     POS_2           0x02
#define     POS_3           0x03
#define     POS_4           0x04
#define     POS_5           0x05
#define     POS_6           0x06
#define     POS_7           0x07
#define     POS_8           0x08
#define     POS_9           0x09
#define     POS_10          0x0A
#define     POS_11          0x0B
#define     POS_12          0x0C
#define     POS_13          0x0D
#define     POS_14          0x0E
#define     POS_15          0x0F
//Direccion de disposito
#define SLAVE_ADDRESS_LCD  0x4E

//Typedef posicion Y


void INIT_LCD(void);				        // Inicializa LCD
void CMD_lcd(uint8_t comando);  			// Envia comando LCD
void CHAR_LCD(uint8_t caracter);  			// Envia dato LCD
void STRING_LCD(uint8_t *pstring);  	    // Envia cadena de caracteres
void LCD_XY(uint8_t x,uint8_t y);           // Posiciona donde escribir
void CLEAR_LCD();                           // Limpia LCD

#endif /* API_INC_DRIVER_LCD_H_ */
