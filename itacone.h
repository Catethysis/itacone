/*

Библиотека itacone - простой доступ к периферии STM32.

Copyright (c) 2013 Catethysis.

https://github.com/Catethysis/itacone
http://catethysis.ru/index.php/stm32-itacone-library/

*/

//Название ядра кристалла
#define stm32f100

//Вспомогательные функции
#include "inc/itacone_misc.h"

//Выбираем файл конфигурации
#ifdef stm32f100
    #include "conf/itacone_conf_stm32f100.h"
#endif