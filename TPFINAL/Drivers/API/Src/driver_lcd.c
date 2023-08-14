/*
 * driver_lcd.c
 *
 *  Created on: Aug 12, 2023
 *      Author: thony
 */

#include "driver_lcd.h"

extern I2C_HandleTypeDef hi2c1_t; //Se trae la estructura hi2c1

void INIT_LCD(void)
{
	while(!(i2c_init()));
	CMD_lcd(LCD_HOME);
	CMD_lcd(LCD_4BITS_MODE);
	CMD_lcd(LCD_ON_CMD);
	CMD_lcd(LCD_POSITION0);
	CMD_lcd(LCD_CLEAR);
}

void CLEAR_LCD()
{
	CMD_lcd(LCD_CLEAR);
}

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
void STRING_LCD(uint8_t *pstring)
{
	while (*pstring) CHAR_LCD(*pstring++);
}

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
