itacone
=======

Adding a simple, arduino-like style to peripheral interaction for STM32.

Использование:

#include "itacone.h"

PC8.mode(OUT).write(HIGH); //Переводим пин PC8 в состояние "выход" и устанавливаем его в состояние "1"

while(1)
{
	PC8.toggle(); //Переключаем пин PC8 в противоположное состояние
	delayMs(200); //Пауза на 200 миллисекунд
}
