/*

Модуль вспомогательных функций для библиотеки itacone

*/

void delayMs(int ms)
{
  int n=(SystemCoreClock/1000/5)*ms; while(n-->0); //Почему 5?
}