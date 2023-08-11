/*
 * driver_keypad.c
 *
 *  Created on: Aug 11, 2023
 *      Author: thony
 */

#include "driver_keypad.h"
static uint8_t letras[n_filas][n_columnas]={{'1','2','3','A'},
						                    {'4','5','6','B'},
						                    {'7','8','9','C'},
						                    {'*','0','#','D'}};


//Funciones para leer las columnas, retorna 1 si esta en alto la entrada y cero si esta en bajo la entrada
static uint8_t Read_COL1(void);
static uint8_t Read_COL2(void);
static uint8_t Read_COL3(void);
static uint8_t Read_COL4(void);
void F1_ON(void);
void F2_ON(void);
void F3_ON(void);
void F4_ON(void);
void F1_OFF(void);
void F2_OFF(void);
void F3_OFF(void);
void F4_OFF(void);
//Funcion que inicia los GPIOs que se utilizaran para el manejo del teclado
void keypad_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0}; //Creacion de variable tipo estructura para configurar los Gpio's
	__HAL_RCC_GPIOA_CLK_ENABLE(); //Habilitacion del clock del bus que se conecta al puerto A
	__HAL_RCC_GPIOB_CLK_ENABLE(); //Habilitacion del clock del bus que se conecta al puerto B
	__HAL_RCC_GPIOC_CLK_ENABLE(); //Habilitacion del clock del bus que se conecta al puerto C

	//Configuracion como salida de los pines correspondientes a las filas
	//FI-Pb4,F2-PB5,F3_PB6,F4_PB7 OUTPUT
	GPIO_InitStruct.Pin = F1_Pin|F2_Pin|F3_Pin|F4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(PORT_F, &GPIO_InitStruct);
	//Configuracion como entrada de los pines correspondientes a las columnas
	//C1-PA6,C2-PA7,C3-PA8,C4-PA9
	GPIO_InitStruct.Pin = C1_Pin|C2_Pin|C3_Pin|C4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(PORT_C, &GPIO_InitStruct);
	//Iniciar con los GPIOs de las filas en estado low
	F1_OFF();
	F2_OFF();
	F3_OFF();
	F4_OFF();
}
//Funcion que retorna el caracter que se presiona en uint8_t
uint8_t keypad_read(void)
{
	uint8_t i=0;
	uint8_t caracter=0;
	for(i=0;i<n_filas;i++)
	{
		if(i==0)//Barrido en fila 1
		{
			F1_OFF();
			F2_ON();
			F3_ON();
			F4_ON();
			HAL_Delay(10);
			while ( !Read_COL1() ){caracter=letras[0][COL1];}	//caracter 1
			while ( !Read_COL2() ){caracter=letras[0][COL2];}	//caracter 2
			while ( !Read_COL3() ){caracter=letras[0][COL3];}	//caracter 3
			while ( !Read_COL4() ){caracter=letras[0][COL4];}	//caracter A
		}
		else if(i==1)//Barrido en fila 2
		{
			F2_OFF();
			F1_ON();
			F3_ON();
			F4_ON();
			HAL_Delay(10);
			while ( !Read_COL1() ){caracter=letras[1][COL1];}	//caracter 4
			while ( !Read_COL2() ){caracter=letras[1][COL2];}	//caracter 5
			while ( !Read_COL3() ){caracter=letras[1][COL3];}	//caracter 6
			while ( !Read_COL4() ){caracter=letras[1][COL4];}	//caracter B
			}
		else if(i==2)//Barrido en fila 3
		{
			F3_OFF();
			F1_ON();
			F2_ON();
			F4_ON();
			HAL_Delay(10);
			while ( !Read_COL1() ){caracter=letras[2][COL1];}	//caracter 7
			while ( !Read_COL2() ){caracter=letras[2][COL2];}	//caracter 8
			while ( !Read_COL3() ){caracter=letras[2][COL3];}	//caracter 9
			while ( !Read_COL4() ){caracter=letras[2][COL4];}	//caracter C
		}
		else if(i==3)//Barrido en fila 4
		{
			F4_OFF();
			F1_ON();
			F2_ON();
			F3_ON();
			HAL_Delay(10);
			while ( !Read_COL1() ){caracter=letras[3][COL1];}	//caracter *
			while ( !Read_COL2() ){caracter=letras[3][COL2];}	//caracter 0
			while ( !Read_COL3() ){caracter=letras[3][COL3];}	//caracter #
			while ( !Read_COL4() ){caracter=letras[3][COL4];}	//caracter D
		}
	}
	return caracter;

}


//Desarrollo funciones de lectura

static uint8_t Read_COL1(void) {
    return (HAL_GPIO_ReadPin(PORT_C, C1_Pin)) ? 1 : 0;
}

static uint8_t Read_COL2(void) {
    return (HAL_GPIO_ReadPin(PORT_C, C2_Pin)) ? 1 : 0;
}

static uint8_t Read_COL3(void) {
    return (HAL_GPIO_ReadPin(PORT_C, C3_Pin)) ? 1 : 0;
}

static uint8_t Read_COL4(void) {
    return (HAL_GPIO_ReadPin(PORT_C, C4_Pin)) ? 1 : 0;
}

//Desarrollo funciones para apagar o encender una fila o columna
void F1_OFF(void){
	HAL_GPIO_WritePin(PORT_F,F1_Pin , GPIO_PIN_RESET);
}

void F2_OFF(void){
	HAL_GPIO_WritePin(PORT_F,F2_Pin , GPIO_PIN_RESET);
}

void F3_OFF(void){
	HAL_GPIO_WritePin(PORT_F,F3_Pin , GPIO_PIN_RESET);
}

void F4_OFF(void){
	HAL_GPIO_WritePin(PORT_F,F4_Pin , GPIO_PIN_RESET);
}

void F1_ON(void){
	HAL_GPIO_WritePin(PORT_F,F1_Pin , GPIO_PIN_SET);
}

void F2_ON(void){
	HAL_GPIO_WritePin(PORT_F,F2_Pin , GPIO_PIN_SET);
}

void F3_ON(void){
	HAL_GPIO_WritePin(PORT_F,F3_Pin , GPIO_PIN_SET);
}

void F4_ON(void){
	HAL_GPIO_WritePin(PORT_F,F4_Pin , GPIO_PIN_SET);
}
