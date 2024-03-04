#define USART_BAUDRATE 9600
#define BAUD_PRESCALE F_CPU / (USART_BAUDRATE *16UL) - 1

//Global var for reading ADC conversion value and keeping track of the ADC input 
//extern volatile unsigned int ADCval; 
extern volatile unsigned int IRcount;
//extern volatile unsigned int ADCval;
extern volatile unsigned int ADCval[2];     //ADCval[0]: soil moisture level, ADCval[1]: water level

void InitADC();