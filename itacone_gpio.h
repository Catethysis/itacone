/*

Модуль ввода-вывода для библиотеки itacone

*/

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
  
  //Функции входа, возвращающие значение
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
  
  //Функции входа, возвращающие пин
  pin in(int *state) { return readIn(state); }
  pin read(int *state) { return readIn(state); }
  
  pin readOut(int *state)
  {
    *state=((ports[this->port]->ODR & this->gpio_pin)==0)?LOW:HIGH;
    return *this;
  }
  
  pin readIn(int *state)
  {
    *state=((ports[this->port]->IDR & this->gpio_pin)==0)?LOW:HIGH;
    return *this;
  }
  
  pin delayMs(int ms)
  {
    int n=(SystemCoreClock/1000/5)*ms; while(n-->0); //Почему 5?
    return *this;
  }
};

pin P0(-1,0);

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