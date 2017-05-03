/**
 * Driver functions for the QTR sensor Array ver. 1.1
 * Created by D. Summerville, 2014
 * Edited by I.Sekyonda 2016
 * Edit for Atmega32u4 on PapilioDUO
 */

#ifndef __QTR_DRIVER_H__
#define __QTR_DRIVER_H__

#include <avr/io.h>
#include <avr/interrupt.h>

//Change these to match the I/O port the QTR is on
#define PORT_QTR PORTD
#define DDR_QTR  DDRD
#define PIN_QTR  PIND

//Define the charge and discharge times
#define QTR_CHARGE_TIME 1   //charge time in whole units of 1/8 ms
#define QTR_DISCHARGE_TIME 24 //discharge time in whole units of 1/8 ms

//Driver public interface
void init_QTR_driver();
unsigned char get_QTR_value();

#endif
