#include "motorController.h"
#include <Arduino.h>
#include <avr/io.h>

void initWaterPump()
{
    //initalize PORTK bit 0 as the control for the water pump
    DDRK |= 0x0F;
    PORTK = 0x01;
}

void turnOffWaterPump()
{
    PORTK = 0x00;
    return;
}

void turnOnWaterPump()
{
    PORTK = 0x01;
    return;
}