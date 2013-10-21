/*

Модуль UART для библиотеки itacone

*/

/*class uart
{
public:
  int number;
  
  void USART1_Config(int divider, int enable_usart, int enable_it)
  {
    RCC->APB2ENR  |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
    GPIOA->CRH	|= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_CNF10_0;
    USART1->BRR = 0x9C4/divider; //Скорость обмена 19200 бод при 24MHz
    USART1->CR1   |= USART_CR1_TE | USART_CR1_RE;
    if(enable_usart==ENABLE_USART) USART1_Enable();
    if(enable_it==ENABLE_IT) { USART1->CR1 |= USART_CR1_RXNEIE; NVIC_EnableIRQ(USART1_IRQn); }
  }
}*/