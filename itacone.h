#define OUT OUTPUT_PP
#define IN INPUT_FL

#define INPUT_AN 0
#define INPUT_FL 1
#define INPUT_PU 2
#define INPUT_PD 3
#define OUTPUT_PP 4
#define OUTPUT_OD 5
#define OUTPUT_AF_PP 6
#define OUTPUT_AF_OD 7

#define SPEED_10 1
#define SPEED_2 2
#define SPEED_50 3

#define HIGH 1
#define LOW 0

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4

void delayMs(int ms)
{
  int n=(SystemCoreClock/1000/5)*ms; while(n-->0); //Почему 5?
}

volatile uint32_t *PORT_ENR[5]={&RCC->APB2ENR, &RCC->APB2ENR, &RCC->APB2ENR, &RCC->APB2ENR, &RCC->APB2ENR},
PORT_ENR_bit[5]={RCC_APB2ENR_IOPAEN, RCC_APB2ENR_IOPBEN, RCC_APB2ENR_IOPCEN, RCC_APB2ENR_IOPDEN, RCC_APB2ENR_IOPEEN};
GPIO_TypeDef *ports[5]={GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};

class pin
{
public:
  int port;
  int gpio_pin;
  int state;
    
  pin(int n_port, int number)
  {
    this->port=n_port;
    this->gpio_pin=1<<number;
  }
  
  pin mode(int state, int speed)
  {
    this->state=state; if((state==INPUT_PU)||(state==INPUT_PD)) write(state&1);
    *PORT_ENR[this->port]|=PORT_ENR_bit[this->port];
    volatile uint32_t *cr=&ports[this->port]->CRL; uint32_t ps=this->gpio_pin;
    if(ps>128) {ps/=256; cr=&ports[this->port]->CRH;} ps=ps*ps*ps*ps; *cr&=~ps*15;
    if(state>3) *cr|=ps*(speed+4*(state&3)); //output
    if(state<4) {if(state>2) state=2; *cr|=ps*4*(state&2);} //input
    return *this;
  }
  
  pin mode(int state) { return mode(state, SPEED_10); }
  
  pin out(int state) { return write(state); }
  pin set(int state) { return write(state); }
  
  pin write(int state)
  {
    ports[this->port]->BSRR = (state==HIGH?this->gpio_pin:this->gpio_pin<<16);
    return *this;
  }
  
  pin high()
  {
    ports[this->port]->BSRR = this->gpio_pin;
    return *this;
  }
  
  pin low()
  {
    ports[this->port]->BRR = this->gpio_pin;
    return *this;
  }
  
  pin toggle()
  {
    if(this->readOut()==LOW) high(); else low();
    return *this;
  }
  
  int in() { return readIn(); }
  int read() { return readIn(); }
  
  int readOut()
  {
    return ((ports[this->port]->ODR & this->gpio_pin)==0)?LOW:HIGH;
  }
  
  int readIn()
  {
    return ((ports[this->port]->IDR & this->gpio_pin)==0)?LOW:HIGH;
  }
  
  pin delayMs(int ms)
  {
    int n=(SystemCoreClock/1000/5)*ms; while(n-->0); //Почему 5?
    return *this;
  }
};

pin
PA0(PORTA,0),   PA1(PORTA,1),   PA2(PORTA,2),   PA3(PORTA,3),   PA4(PORTA,4),
PA5(PORTA,5),   PA6(PORTA,6),   PA7(PORTA,7),   PA8(PORTA,8),   PA9(PORTA,9),
PA10(PORTA,10), PA11(PORTA,11), PA12(PORTA,12), PA13(PORTA,13), PA14(PORTA,14),
PA15(PORTA,15),

PB0(PORTB,0),   PB1(PORTB,1),   PB2(PORTB,2),   PB3(PORTB,3),   PB4(PORTB,4),
PB5(PORTB,5),   PB6(PORTB,6),   PB7(PORTB,7),   PB8(PORTB,8),   PB9(PORTB,9),
PB10(PORTB,10), PB11(PORTB,11), PB12(PORTB,12), PB13(PORTB,13), PB14(PORTB,14),
PB15(PORTB,15),

PC0(PORTC,0),   PC1(PORTC,1),   PC2(PORTC,2),   PC3(PORTC,3),   PC4(PORTC,4),
PC5(PORTC,5),   PC6(PORTC,6),   PC7(PORTC,7),   PC8(PORTC,8),   PC9(PORTC,9),
PC10(PORTC,10), PC11(PORTC,11), PC12(PORTC,12), PC13(PORTC,13), PC14(PORTC,14),
PC15(PORTC,15),

PD0(PORTD,0),   PD1(PORTD,1),

P0(-1,0);

class pins
{
public:
  pin *pin_ar;
  int n_pins;
  
  pins(pin pin1, ...)
  {
    volatile int *i=(int*)&pin1;
    if(*i>-1)
      n_pins+=*i;
    /*pin *p = &pin1;
    n_pins=0; while((*p).port>-1) {pin_ar[n_pins++]=*p; p+=2;};
    n_pins--;*/
  }
  /*
  pins(pin* pin1)
  {
  }*/
};

/*
class uart
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