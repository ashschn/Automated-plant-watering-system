#include "LCD.h"

//Function Definitions
void LCD_init()
{
    DDRA = 0xF0; //initalize data write pins for LCD 
    DDRB = 0x23; //Initalize enable and reset pins for LCD
    //wait for power up - more than 30 ms for vdd to rise to 4.5v
    _delay_ms(100);

    //Note that we need to resetr the controller to enable 4-bit mode
    LCD_E_RS_init();    //Set the E and RS pins active low for each LCD reset

    //Reset and wait for activation
    LCD_write_4bits(LCD_Reset);
    _delay_ms(10);

    //Now we can set the LCD to 4-bit mode
    LCD_write_4bits(LCD_4bit_enable);
    _delay_us(80);    //delay must be > 39us
    /*
    System reset is complete - set up LCD modes

    At this point we are operating in 4-bit mode
    (which means we ahve to send the high nibble and low-nibble separate)
    and can now set the line numbers and font size
    Notice: we use the "LCD_write_4bits()" when in 8-bit mode and the LCD_instruiction() (this just makes
    use of two calls to the LCD_write)4bits() function)
    once we're in 4-bit mode/ The set of instructions are found in Table 7 of the datasheet.
    */
    LCD_write_instruction(LCD_4bit_mode);
    _delay_us(80);

    //from page 26 (and table 7) in the datasheet we need to :
    //display = off, display = clear, and enttry mode = set
    LCD_write_instruction(LCD_4bit_displayOFF);
    _delay_us(80);

    LCD_write_instruction(LCD_4bit_displayCLEAR);
    _delay_ms(80);

    LCD_write_instruction(LCD_4bit_entryMODE);
    _delay_us(80);

    //The LCD should now be initialized to operate in 4-bit mode, 2 lines, 5x8 dot fontsize
    //Need to turn the display back on for use
    LCD_write_instruction(LCD_4bit_displayON);
    _delay_us(80);
}

void LCD_E_RS_init(void)
{
    //Set up the E and RS lines to active low for the reset function
    PORTB &= ~(1<<LCD_EnablePin);
    PORTB &= ~(1<<LCD_RegisterSelectPin);
}

void LCD_write_4bits(uint8_t Data)
{
//we are only interested in sending the data to the upper 4 bits of PORTA
  PORTA &= 0b00001111;    //ensure the upper bybble of PORTA is cleared
  PORTA |= Data;          //Write the data to the data lines on PORTA

  //The data is now sitting on the upper nybble of PORTA - need to pulse enable to send it
  LCD_EnablePulse();    //Pulse the enable to write/read the data
}

//Pulse the Enable pin on the LCD controller to write/read the data lines - should be at least 230ns pulse width
void LCD_EnablePulse(void)
{
    //Set the enable bit low -> high -> low
    //PORTB &= ~(1<<LCD_EnablePin); Sets enable low
    //_delay_us(1) waits to ensure the pin is low
    PORTB |= (1<<LCD_EnablePin);    //Set enable high
    _delay_us(1);
    PORTB &= ~(1<<LCD_EnablePin);
    _delay_us(1);
}

void LCD_write_instruction(uint8_t Instruction)
{
    //ensure that RS is low
    //PORTB &= ~(1<<LCD_RegisterSelectPin)
    LCD_E_RS_init();    //Set the E and RS pins active low for each LCD reset

    LCD_write_4bits(Instruction);       //write the high nybble first
    LCD_write_4bits(Instruction<<4);    //write the low nybble
}

//Write Character to the display
void LCD_write_char(char Data)
{
    //Set up the E aand Rs Lines for data writing
    PORTB |= (1<<LCD_RegisterSelectPin);   //Ensurs RS pin is set high
    PORTB &= ~(1<<LCD_EnablePin); //Ensure the enable pin is low

    LCD_write_4bits(Data); //wire the upper nybble
    LCD_write_4bits(Data<<4); //write the lower nybble
    _delay_us(80);
}

void InitUSART()
{
    // Enable RX and RX //
    UCSR0B |= 0x18;
    // Use 8-bit character frames in asynchronous mode //
    UCSR0C |= 0x06;

    // set the baud rate (upper 4 bits should be zero) //
    UBRR0L = BAUD_PRESCALE;
    UBRR0H = (BAUD_PRESCALE >> 8); 
    }