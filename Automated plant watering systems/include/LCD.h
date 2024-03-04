#include <avr/io.h>
#include <util/delay.h>

/***************************************************
 * setup:
 * LCD                 ATMega2560
 * D6 -------------------> PA7
 * D5 -------------------> PA6
 * D4 -------------------> PA5
 * D7 -------------------> PA4
 * E  -------------------> PB1
 * RW -------------------> GND
 * RS -------------------> PB0
 * 
*****************************************************/

//Helpful LCD controls defines 
#define LCD_Reset                 0b00110000    //reset the LCD to put in 4-bit mode
#define LCD_4bit_enable           0b00100000    //4-bit data - can't set the line display or fonts until this is set
#define LCD_4bit_mode             0b00101000    //2-line display, 5x8 font
#define LCD_4bit_displayOFF       0b00001000    //set display off
#define LCD_4bit_displayON        0b00001100    //set display on - no blink
#define LCD_4bit_displayON_B1     0b00001101    //set display on - with blink
#define LCD_4bit_displayCLEAR     0b00000001    //replace all chars with "space"
#define LCD_4bit_entryMODE        0b00000110    //set curser to write/read from left to right
#define LCD_4bit_cursorSET        0b10000000    //set cursor position
#define LINE_MASK                 0b01000000    //change between lines
#define LCD_PLEASE_HELP           0b00000010

//For two line mode
#define LineOneStart    0x00
#define LineTwoStart    0x40    //must set DDRAM address in LCD controller for line two

//Pin definitions for PORTB control lines
#define LCD_EnablePin           1
#define LCD_RegisterSelectPin   0

//USART0 setup
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE F_CPU / (USART_BAUDRATE *16UL) - 1

//Prototypes
void LCD_init();
void LCD_E_RS_init(void);
void LCD_write_4bits(uint8_t);
void LCD_EnablePulse(void);
void LCD_write_instruction(uint8_t);
void LCD_write_char(char);
void InitUSART();