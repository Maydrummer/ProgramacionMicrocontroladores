# TP FINAL
## Tema: Sistema electronico de seguridad.
### Aplicacion
Este sistema de seguridad electrónica se encargara de monitorear un cuarto mediante un sensor radar de microondas basado en efecto Doppler.
Tiene una interfaz de usuario que permita armar y desarmar la alarma además, una alarma visual que indicara cuando se haya detectado un intruso.

### Objetivos
- Desarrollar una maquina de estado que determine el comportamiento de la aplicación.

- Usar los periféricos: GPIO, UART e I2C.

- Modularizar el código para subdividir tareas.

- Emplear funciones, variables que sean publicas y privadas.

### Microcontrolador usado

__Microcontrolador:__ STM32F446RET6

__Placa de desarrollo:__ Placa Nucleo F446RE

### Modulos usados
- Pantalla LCD 16x2 con modulo I2C integrado
- Teclado matricial 4x4 
- Diodo Led
- Sensor RCWL-0516
- Radar HLK-LD303-24G
### Pines utilizados
|Pines         | Funcion      | Modulo       |
|--------------|--------------|--------------|
|PB8           |SCL I2C1          | Pantalla LCD    |
|PB9           |SDA I2C1          | Pantalla LCD    |
|PB4,PB5,PB6,PB10|GPIOB-Salidas   | Teclado 4x4     |
|PA6,PA7,PA8,PA9|GPIOB-Entradas   | Teclado 4x4     |
|PA1           |TX Uart4          | Radar           |
|PA0           |RX Uart4          | Radar           |
|PA2           |TX Uart2          | Terminal PC     |
|PA3           |RX Uart2          | Terminal PC     |
|PA10          |GPIOA-Salida      | Diodo Led Rojo  |