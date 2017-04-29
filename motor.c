/**
* Driver functions for the DAGU Rover 5
* Created by I.Sekyonda 2016
* For Atmega32u4 on PapilioDUO
*Include  motor.h in your main.c file and you can call these functions
*/

#include "motor.h"


/*initialize the PORTs dedicated to the motors.
You always have to call this in main to intialize the PORT I/O
*/
void init_motors (){

	//DDRD |= ((1<<2)|(1<<3) |(1<<7) | (1<<6))
    port(DDR,leftmotorport) |= ((1<<leftmotora) | (1<<leftmotorb));
    port(DDR,rightmotorport) |=  ((1<<rightmotora) | (1<<rightmotorb));

	//DDRB &= (~(1<<5) & ~(1<<4))
    port(DDR,leftquadport) &= (~(1<<leftquada) & ~(1<<leftquadb));

	//DDRD &= (~(1<<1) & ~(1<<4))
    port(DDR,rightquadport) &= (~(1<<rightquada) & ~(1<<rightquadb));

}

void leftmotor_reverse(){

    port(PORT,leftmotorport) |= (1<<leftmotora);
    port(PORT,leftmotorport) &= ~(1<<leftmotorb);

}


void rightmotor_reverse(){

    port(PORT,rightmotorport) |=  (1<<rightmotorb);
    port(PORT,rightmotorport) &=  ~(1<<rightmotora);
}


void leftmotor_brake(){

    port(PORT,leftmotorport) |= ((1<<leftmotora) | (1<<leftmotorb));
}

void rightmotor_brake(){

    port(PORT,rightmotorport) |=  ((1<<rightmotora)| (1<<rightmotorb));

}


void leftmotor_forward(){

    port(PORT,leftmotorport) |= (1<<leftmotorb);
    port(PORT,leftmotorport) &= ~(1<<leftmotora);

}

void rightmotor_forward(){

    port(PORT,rightmotorport) &=  ~(1<<rightmotorb);
    port(PORT,rightmotorport) |=  (1<<rightmotora);
}

void leftmotor_coast(){

    port(PORT,leftmotorport) &= (~(1<<leftmotora) & ~(1<<leftmotorb));

}

void rightmotor_coast(){
    port(PORT,rightmotorport) &=  (~(1<<rightmotora) &  ~(1<<rightmotorb));

}


uint8_t leftquad_value(){
    return ((port(PIN,leftquadport)));

}

 uint8_t rightquad_value(){
    return ((port(PIN,rightquadport)));

}


void brake(){
    leftmotor_brake();
    rightmotor_brake();
}
