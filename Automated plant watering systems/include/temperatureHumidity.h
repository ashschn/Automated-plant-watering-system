/**
 * temperatureHumidity.h
 * 
 * Uses DHT11 sensor 
 * 
 * 
 * 
 * 
*/
#include "avr/delay.h"

#define SET_BIT(byte, bit) (byte |= (1 << bit))
#define CLEAR_BIT(byte, bit) (byte &= ~(1 << bit))
#define IS_SET(byte, bit) ((byte) & (1 << bit))

void Timer_delay_check_ascii(void);

void dht11Init();
int dht11FindResponse();
int dht11ReceiveData(uint8_t x[]);
int dht11_find_response10();