/**
 * Driver functions for the QTR sensor Array ver. 1.1
 * Created by D. Summerville, 2014
 * Edited by I.Sekyonda 2016
 * Edit for Atmega32u4 on PapilioDUO
 */

#include "qtr_driver.h"

unsigned char QTR_ARRAY_VALUE; //variable holding current QTR sensor state

//returns the current state of the QTR array
unsigned char get_QTR_value()
{
    return QTR_ARRAY_VALUE;
}

//initializes the QTR interrupt-based driver
void init_QTR_driver()
{
    QTR_ARRAY_VALUE=0x00; //initial value
    DDR_QTR=0x00;   //configure port as input...
    PORT_QTR=0x00;  //in order to deactivate pull-up resistors
    OCR0B = QTR_CHARGE_TIME; //time we turn off the array charge
    OCR0A = QTR_DISCHARGE_TIME; //time we read the array
    TCCR0A |= (1<<WGM01); //configure counter to reset at QTR_DISCHARGE_TIME
    TIMSK0 |= (1 << OCIE0A) | (1 << OCIE0B);  //enable interrupts
    TCCR0B |= ((1<<CS02) | (1<<CS00)); //set counter prescaler to 1024 and start counter
    sei(); //enable global interrupts
    return;
}
void QTR_CHARGE_ARRAY()
{
    PORT_QTR=0xFF; //set array ping to output, then
    DDR_QTR=0xFF; //output 0xFF to QTR pins to charge array
    return;
}
ISR(TIMER0_COMPB_vect)
{
    DDR_QTR = 0x00;  //configure QTR port as input to start discharging
    return;
}
ISR(TIMER0_COMPA_vect)
{
    QTR_ARRAY_VALUE=PIN_QTR; //read current sensor value
    QTR_CHARGE_ARRAY(); //begin chrging array for next read
    return;
}
