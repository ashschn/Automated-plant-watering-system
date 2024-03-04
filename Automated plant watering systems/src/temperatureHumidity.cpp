#include "temperatureHumidity.h"
#include <Arduino.h>
#include <avr/io.h>


uint8_t data[5];


/**
 * 1.)CPU frequency is 16Mhz
 * 2.) max timer counter value (256 for 8 bits and 65536 for 16 bit timer)
 * 3.) divide CPU frequency through the cohosen prescalar 
 *      for timer0, prescalar 8 -> 16000000 / 8 = 2000000
 *      for timer 1, prescalar 1024 -> 16000000 / 1024 = 15625
 * 4.) divide result through the desired frequency 
 *      F = 1 / 40us -> 25 kHz
 *      2000000 / 25000 = 80 counts in TCNT0 to wait 40 us
 *      F = 1/ 18ms -> 55.5555 Hz
 *      15625 / 55.5555  = 281 counts in TCNT1 to wait 18 ms
 *  5.) verify value is   
*/

//uses timer 1 and timer0
void dht11Init()
{
    TCCR1B = (1 << CS12 ) | (1 << CS10);   //Timer/counter 1 control register B  with prescalar 1024
    TCNT1 = 0;

    TCCR0B |= (1 << CS01);      //timer/counter 0 control register B, 16Mhz /8 (from prescalar)
                                //frequency: 2 MHz, Period 0.5 us, Overflow: 128 us*/
                                //frequency: 2 MHz, Period 0.5 us, Overflow: 128 us
    TCNT0 = 0;                  //current count value

    SET_BIT(DDRH,PH4);       //DDRH |= (1 << PH4);  //In idle state, data bus is HIGH
    PORTH &= ~0x10;    //Host send a 0V on the data bus (>18 ms) (start signal)

    TCNT1 = 0;
    while(TCNT1 <= 281);

    SET_BIT(PORTH, PH4);    //PORTH |= (1 << PH4); //Host pull up the data bus for (20-40 us) (wait for response)
    TCNT0 = 0;
    while(TCNT0 <= 80);     //80 counts to wait 40 us then sets databus low
    DDRH &= ~0x10;
}

int dht11FindResponse()
{
    if(!(IS_SET(PINH,PH4)))
    { 
        TCNT0 = 0;
        while(TCNT0 <= 170);
    }
    else
        return -1;
    if(IS_SET(PINH,PH4))
    { 
        TCNT0 = 0;
        while(TCNT0 <= 170); 
    }
    else
        return -1;
    return 0;
}

int dht11ReceiveData(uint8_t *x)
{
    uint8_t check;
    volatile uint8_t cnt = 0;
    char buffer[100];
    uint8_t i = 0;

    for(int z = 0; z < 5; ++z)
    {
        for(int j = 7; j >= 0; --j)
        {
            i = 0;
            TCNT0 = 0;
            while(!IS_SET(PINH,PH4))    //waits until dht is set high
            {
                if(TCNT0 >= 120)
                {
                    return 12;
                }
            }

            TCNT0 = 0;
            while(IS_SET(PINH,PH4)) //waits until dht is set low
            {
                i = 0;
                if(TCNT0 <= 160)
                cnt = TCNT0;
                else{
                    return 1;
                }
            }
            
            //1-bit transmit is '0'
            if((cnt >= 40) & (cnt <= 70))
            CLEAR_BIT(data[z],j);

            else if((cnt >= 120) & (cnt <= 160)) //1-bit transmit is '1'
            SET_BIT(data[z],j);
            
            else    //should never enter here
            {
                return 2;
            }
        }
    }

    /*check = (data[0] + data[1] + data[2] + data[3]) & 0xFF;
    if(check != data[4]) return 3;
    for(int w = 0; w <= 4; w++)
    {
        x[w] = data[w];
    }*/
    for(int w = 0; w <= 4; w++)
    {
        x[w] = data[w];
    }
    return 0;   //it should be returning 0, if it's returning anything else there is something wrong
}