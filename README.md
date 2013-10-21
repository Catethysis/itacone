itacone
=======

Adding a simple, arduino-like style to peripheral interaction for STM32.  
Добавляем в STM32 простой синтаксис для общения с периферией в стиле ардуино, плюс синтаксический сахар.

Использование:

`#include "itacone.h"

PC8.mode(OUT).write(HIGH); //Переводим пин PC8 в состояние "выход" и устанавливаем его в состояние "1"

while(1)
{
	PC8.toggle(); //Переключаем пин PC8 в противоположное состояние
	delayMs(200); //Пауза на 200 миллисекунд
}`

##Модуль GPIO
Модуль GPIO содержит функции:

pin.mode (INPUT_AN | INPUT_FL | INPUT_PU | INPUT_PD | OUTPUT_PP | OUTPUT_OD | OUTPUT_AF_PP | OUTPUT_AF_OD, [SPEED_2 | SPEED_10 | SPEED_50])  
Задаёт режим и скорость работы пина.

pin.out (LOW | HIGH) или pin.write(LOW | HIGH)  
Выводит бит в пин - устанавливает пину переданное состояние.

pin.high()  
Переводит пин в "1"

pin.low()  
Переводит пин в "0"

pin.toggle()  
Переключает пин на противоположное состояние

pin.in() == LOW | HIGH или pin.out() == LOW | HIGH или pin.readIn() == LOW | HIGH  
Читает состояние пина, настроенного на вход

pin.readOut() == LOW | HIGH  
Читает состояние пина, настроенного на выход

Все функции (кроме функций чтения состояния) возвращают pin, поэтому вызовы можно соединять в цепочки:
PC8.mode(OUTPUT_PP, SPEED_2).high();  