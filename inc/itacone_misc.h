/*

Модуль вспомогательных функций для библиотеки itacone

*/

void delayMs(int ms)
{
  int n=(SystemCoreClock/1000/5)*ms; while(n-->0); //Почему 5?
}

uint16_t Unique_ID_Low0(void) { return *(u16*)(0x1FFFF7E8); };
uint16_t Unique_ID_Low1(void) { return *(u16*)(0x1FFFF7EA); };
uint32_t Unique_ID_Low (void) { return *(u32*)(0x1FFFF7E8); };
uint32_t Unique_ID_Mid (void) { return *(u32*)(0x1FFFF7EC); };
uint32_t Unique_ID_Hig (void) { return *(u32*)(0x1FFFF7F0); };