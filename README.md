itacone
=======

Adding a simple, arduino-like style to peripheral interaction for STM32.  
Добавляем в STM32 простой синтаксис для общения с периферией в стиле ардуино, плюс немного синтаксического сахара.

Использование:

	include "itacone.h"

	PC8.mode(OUT).write(HIGH); //Переводим пин PC8 в состояние "выход"
	//и устанавливаем его в состояние "1"

	while(1)
	{
		PC8.toggle(); //Переключаем пин PC8 в противоположное состояние
		delayMs(200); //Пауза на 200 миллисекунд
	}

##Поддержка разных микроконтроллеров
По возможности код пишется платформонезависимо - так, чтобы для перехода на другой микроконтроллер достаточно было заменить конкретные адреса регистров и учесть особенности (количество, тип) имеющейся периферии. На текущий момент библиотека поддерживает лишь один кристалл - STM32F100RBT6, но это только начало. Ближайшие планы - это добавить поддержку STM32F050, а также STM32F407 и STM32F305.

##Цели и применимость
Цель - полное избавление от ST-шной библиотеки StdPeriph. Пока что реализован только модуль общения с GPIO, сейчас идёт разработка модулей USART и таймера.

Вся библиотека рассчитана на то, что вы знаете, что делаете, поэтому внутри процедур нет никаких проверок входящих параметров - более того, вы вполне можете настроить пин на вход и попытаться что-то в него вывести. В определённом случае у вас это получится и даже будет кое-как работать (если настроен вход с подтяжкой) - но всё использование as is. Этот подход даёт возможность тратить поменьше времени разработки на побочные функции, а самое главное - ускоряет код. Приоритет именно в простоте использования и скорости работы.

##Архитектура
Библиотека сделана по модульной архитектуре, чтобы обеспечить простое изучение и облегчить дальнейшую разработку. Также в отдельный файл выделена вся платформозависимая часть - настройки конфигурации микроконтроллера. Теперь для миграции на другой кристалл достаточно лишь заменить файл itacone_conf_xxx.h.

##Модуль GPIO
Используем простые функции для обращения к портам ввода-вывода, а к самым часто используемым есть ещё и алиасы-сокращения. И конечно, не забывайте объединять вызовы в цепочки!

####Переменные-пины
У вас сразу есть переменные вроде PA4 или PC13 (типа pin), к которым вы можете обращаться всякими удобными функциями, например так:

```c
PC8.mode(OUTPUT_PP, SPEED_2).high();
```

Можно задать копию переменной пина, сложив её в переменную типа pin, и использовать дальше именно эту копию:

```c
pin _pin1=PB3;
_pin1.mode(OUTPUT);
```

Да и совместить всё в одну операцию:

```c
pin _pin2=PD1.mode(INPUT);
```

И наконец, всё это делать в цикле:

```c
while(1)
{
	_pin1.high();
	sleep(100);
	_pin1.low();
	sleep(100);
	_pin1.out(_pin2.in());
	sleep(500);
}
```

Перечислю все полезные функции.
###Настройка пина
####pin.mode (mode, [speed])
Задаёт режим и скорость работы пина, и инициализирует его.  
```c
pin.mode (OUTPUT_PP | OUTPUT_OD | OUTPUT_AF_PP | OUTPUT_AF_OD |
INPUT_AN | INPUT_FL | INPUT_PU | INPUT_PD, [SPEED_2 | SPEED_10 | SPEED_50]);
//возвращает снова тот же pin
```
####Параметры настройки входа/выхода
OUTPUT_PP - выход в режиме пуш-пулл.  
OUTPUT_OD - выход с открытым коллектором.  
OUTPUT_AF_PP - выход периферии в режиме пуш-пулл.  
OUTPUT_AF_OD - выход периферии с открытым коллектором.  
INPUT_AN - вход для АЦП.  
INPUT_FL - "плавающий" вход, или третье (высокоимпедансное) состояние.  
INPUT_PU - вход со слабой подтяжкой к "+".  
INPUT_PD - вход со слабой подтяжкой к "-".
####Параметры скорости выхода
SPEED_2 - максимальная скорость переключения пина - 2МГц.  
SPEED_10 - максимальная скорость переключения пина - 10МГц.  
SPEED_50 - максимальная скорость переключения пина - 50МГц.  
Этот параметр настраивает slope rate - скорость нарастания/убывания напряжения, от него зависит резкие будут фронты/спады или плавные.
###Вывод
####pin.out (state) или pin.write(state) или pin.set(state)
Выводит бит в пин - устанавливает пину переданное состояние.  
```c
pin.out (LOW | HIGH);
pin.write (LOW | HIGH);
pin.set (LOW | HIGH);
//возвращает снова тот же pin
```
####pin.high()
Переводит пин в "1".
####pin.low()
Переводит пин в "0".
####pin.toggle()
Переключает пин на противоположное состояние.
###Ввод
Сначала - функции ввода, возвращающие значение состояния. С ними чейнинг невозможен.
####pin.in() или pin.read() или pin.readIn()
Читает состояние пина, настроенного на вход.  
```c
int a = PC6.in();
int b = PA3.read();
int c = PB11.readIn();
//возвращает LOW или HIGH
```
####pin.readOut()
Читает состояние пина, настроенного на выход.  
```c
int c = PA5.readOut();
//возвращает LOW или HIGH
```
Теперь - функции ввода, возвращающие пин. Их можно чейнить.
####pin.in(state) или pin.read(state) или pin.readIn(state)
Читает состояние пина, настроенного на вход.  
```c
int a, b, c;
PC6.in(&a);
PA3.read(&b);
PB11.readIn(&c);
//возвращает обратно пин
```
####pin.readOut()
Читает состояние пина, настроенного на выход.  
```c
int a;
PA5.readOut(&a);
//возвращает пин
```
###Вспомогательные функции
####pin.delayMs(int ms)
Пауза на ms миллисекунд. Удобна тем, что возвращает pin. Не забывайте, что пауза впустую расходует ресурсы процессора, не выполняя полезной работы. По возможности делайте паузы аппаратным таймером.
###Цепочки
Все функции (кроме функций чтения состояния) возвращают pin, поэтому вызовы можно соединять в цепочки:

```c
int a, b;
b = PC8. mode(OUTPUT). high() .delayMs(300). low(). delayMs(500). mode(INPUT). read(&a). delayMs(1000). read();
```

В этом примере мы назначаем пин PC8 "выходом", на 300 миллисекунд выводим в него "1", потом на 500 миллисекунд выводим "0", переводим пин во "вход" и читаем его значение в переменную a, а через секунду - снова читаем состояние и возвращаем его в переменную b.

Это удобно, например, для выполнения в цикле.

##Модуль misc
Пока здесь только функция паузы.
####delayMs(int ms)
Пауза на ms миллисекунд. Не забывайте, что пауза впустую расходует ресурсы процессора, не выполняя полезной работы, поэтому по возможности делайте паузы аппаратным таймером.