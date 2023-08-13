/*
 * driver_i2c1.c
 *
 *  Created on: Aug 12, 2023
 *      Author: thony
 */
#include "driver_i2c1.h"

I2C_HandleTypeDef hi2c1_t;
extern UART_HandleTypeDef huart2;
void gpio_i2c_config(void)
{
	GPIO_InitTypeDef i2c_gpio={0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	i2c_gpio.Pin=GPIO_PIN_8|GPIO_PIN_9;
	i2c_gpio.Mode=GPIO_MODE_AF_OD; //Funcion alterna y lo dejamos en OPEN DRAIN,ya que I2C se maneja asi
	i2c_gpio.Pull=GPIO_PULLUP;//Para poner en pull UP sd y scl
	i2c_gpio.Speed=GPIO_SPEED_FREQ_VERY_HIGH;//Debe ser alta la frecuencia debido a que seran pines de comunicacion
	i2c_gpio.Alternate=GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &i2c_gpio);

}
bool_t i2c_init(void)
{
	bool_t state_i2c_init=false;
	gpio_i2c_config();
	__HAL_RCC_I2C1_CLK_ENABLE();
	hi2c1_t.Instance = I2C1;
	hi2c1_t.Init.ClockSpeed = 100000;
	hi2c1_t.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1_t.Init.OwnAddress1 = 0;
	hi2c1_t.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1_t.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1_t.Init.OwnAddress2 = 0;
	hi2c1_t.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1_t.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1_t) == HAL_OK)
	{
		state_i2c_init=true;
		enviar_stringCompleto_uart((uint8_t*)"I2C1 Inicializado...\r\n", huart2);

	}
	return state_i2c_init;
}

void scan_address(void)
{
	  char txt2[scan_address_length];
	  for(uint8_t address=0;address< max_slave ; address++)
	  {
		  bool_t ack=HAL_I2C_IsDeviceReady(&hi2c1_t, address<<desplazamiento_7_bits, trial_scan, timeout_scan); //Al enviarse 8 bits siempre, y la direccion es de 7, se hace desplazamiento de 1 a la izquierda
		  if(ack == HAL_OK)
		  {
			  sprintf((char*)txt2,"Dispositivo encontrado 0x%X\n\r",address<<desplazamiento_7_bits);
			  enviar_stringCompleto_uart((uint8_t*)txt2, huart2);
		  }
	  }
}
