#include "soilMoisture.h"
#include <avr/io.h>
#include <avr/interrupt.h>

//definitions of global
//volatile unsigned int ADCval = 0;
volatile unsigned int ADCval[2] = { 0, 0};
volatile unsigned int IRcount = 0;

void InitADC()
{
  DDRF = 0x00;  //ADC input 
  UCSR0B |= 0x18; //these lines already in initusart
  UCSR0C |= 0X06;

  UBRR0L = BAUD_PRESCALE;
  UBRR0H = BAUD_PRESCALE >> 8;

  //DDRK |= 0x0F ; //set PORTA as an output
  //PORTK = 0XFF; //PORTA pin 0 and 1 as output for on/off indicator and LED x/y-axis levels
  DDRD = 0xFF; //set PORTD0 as an output (int pin)
  PORTD = 0x01; //set PORTD to a known state

  EICRA = 0XFF;
  EICRB = 0X01;

  EIMSK |= 0X1F;

  //This is the adc stuff
  ADCSRA |= 0x8F;
  ADMUX |= 0x40;
  

  /*//Setting up timer0
  DDRB = 0xFF;
  PORTB = 0xFF;*/

  ADCSRA |= 0x40; //start first conversion
  sei(); //enable global interrupts

  /*//more timer2 setup
  TCCR2A = 0xA3;
  TCCR2B = 0x05;
  TCNT2 = 0x00;
  OCR2B = 192;*/

  /*//setting up timer2
  TCCR2A = 0xA7;    //Set to fast PWM (we want to change be able to set top value)
  TCCR2B = 0x05;
  TCNT2 = 0x00;
  OCR2B = 192;*/

}

ISR(ADC_vect)
{
  //ADCval = ADCW; //ADCW: stores entire result
  //ADMUX = 0x40; //sets channel (don't think we need this line)

  ADCval[IRcount] = ADCW;
  switch(IRcount)
  {
    case 0:
      ADMUX = 0X41; 
      IRcount++;
      break;
    case 1:
      ADMUX = 0x40; 
      IRcount = 0;
      break;
    default: break;
  }

  //start another conversion
  ADCSRA |= 0x40;
}