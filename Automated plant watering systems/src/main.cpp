#include <Arduino.h>
#include <avr/io.h>
#include "motorController.h"
#include "temperatureHumidity.h"
#include "LCD.h"
#include "soilMoisture.h"


int main()
{
  /*//Testing for the LCD display
  DDRA = 0xF0; //initalize data write pins for LCD //TODO:maybe move these two intalize pin lines to LCD_init()
  DDRB = 0x23; //Initalize enable and reset pins for LCD
  //Initalize the LCD for a 4-bit mode, two ines and 5x8 dots 
  //Inits found on page 26 of datasheet and Table 7 for function set instructions
  LCD_init(); 
  //InitUSART();
  char debugChar = 'a';
  
  //Write a single character
  LCD_write_char(debugChar);

  //line two
  LCD_write_instruction(LCD_4bit_cursorSET | LineTwoStart);
  _delay_us(80);
  debugChar = 'b';
  LCD_write_char(debugChar);*/

  //Init Water pump
  initWaterPump();
  uint16_t temperature;
  uint16_t humidity;
  uint16_t waterLevel;

  //Inits for LCD
  LCD_init(); 
  char temperatureDisplay[20];
  char humidityDisplay[20];
  char waterLevelDisplay[20];
  char ch=176;

  //initialization for humidity and temperature sensor
  InitUSART();
  uint8_t dht11Data[5];
  char buffer[100];
  uint8_t i = 0;
  uint8_t temp; 

  //Soil Moisture Sensor
  InitADC();

  /*//Testing Moisture meter
  char buffer[100];
  InitUSART();
  uint8_t i = 0;*/
  turnOffWaterPump();   //While switch is open and power supply is turned on, it gets messed
  _delay_ms(3000);
  while(1)
  {

    //turning on/off water pump
    if(ADCval[0] > 520)
    {
      turnOnWaterPump();
    }
    else
    {
      turnOffWaterPump();
    }

    //Get current temperature/ humidity
    dht11Init();
    dht11FindResponse();
    temp = dht11ReceiveData(dht11Data); //temp value used for debugging


    //Display Temperature
    temperature = float(1.8*dht11Data[2])+32;
    sprintf(temperatureDisplay,"Temp: %d F\n", temperature);
    //sprintf(temperatureDisplay,"Temp: %d.%  \d\n", dht11Data[2], dht11Data[3]);
    LCD_write_instruction(LCD_4bit_displayCLEAR);
    _delay_ms(80);
    LCD_write_instruction(LCD_4bit_cursorSET | LineOneStart);
    _delay_us(80);
    //LCD_write_char('a');
    i = 0;
    while(temperatureDisplay[i] != '\n')
    {
      LCD_write_char(temperatureDisplay[i]);
      i++;
    }

    //Display Humidity
    humidity = dht11Data[0];
    sprintf(humidityDisplay,"Humidity: %d%%\n", humidity);
    //sprintf(temperatureDisplay,"Temp: %d.%d\n", dht11Data[2], dht11Data[3]);
    LCD_write_instruction(LCD_4bit_cursorSET | LineTwoStart);
    _delay_us(80);
    //LCD_write_char('a');
    i = 0;
    while(humidityDisplay[i] != '\n')
    {
      LCD_write_char(humidityDisplay[i]);
      i++;
    }

    _delay_ms(3000);

    //Update system again
    if(ADCval[0] > 520)
    {
      turnOnWaterPump();
    }
    else
    {
      turnOffWaterPump();
    }

    //Get current temperature/ humidity
    dht11Init();
    dht11FindResponse();
    temp = dht11ReceiveData(dht11Data); //temp value used for debugging

    //Display Water level
    //waterLevel = float(ADCval[1]/1023)*100;
    waterLevel = float(ADCval[1]/2.7);
    if (waterLevel > 100)
    {
      waterLevel = 100;
    }
    sprintf(waterLevelDisplay,"Water Level: %d%%\n", waterLevel);
    //sprintf(temperatureDisplay,"Temp: %d.%d\n", dht11Data[2], dht11Data[3]);
    LCD_write_instruction(LCD_4bit_displayCLEAR);
    _delay_ms(80);
    LCD_write_instruction(LCD_4bit_cursorSET | LineOneStart);
    _delay_us(80);
    //LCD_write_char('a');
    i = 0;
    while(waterLevelDisplay[i] != '\n')
    {
      LCD_write_char(waterLevelDisplay[i]);
      i++;
    }

    _delay_ms(3000);


    //Testing the mositure meter
    sprintf(buffer,"\nMoisture Level:%d, Water Level:%d", ADCval[0], ADCval[1]);
    i = 0;
    while( buffer[i] != '\0')
    {
      while((UCSR0A & (1 << UDRE0)) == 0) {};
      UDR0 = buffer[i];
      i++;
    }

    //Testing the Humidity and temperature sensor
    sprintf(buffer, "\nHumidity: %d.%d, Temperature: %d.%d, Returned value: %d", dht11Data[0], dht11Data[1], dht11Data[2], dht11Data[3], temp);
    i = 0;
    while(buffer[i] != '\0')
    {
      while((UCSR0A & (1 << UDRE0)) == 0){};
      UDR0 = buffer[i];
      i++;
    }
  }
  return -1;
}