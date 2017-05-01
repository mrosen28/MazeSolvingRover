#define F_CPU 1000000UL
#include "motor.c"
#include "qtr_driver.c"

int main() {
  //RoverSetup
  init_motors ();
  init_QTR_driver();

  DDRC = 0xFF;

  while (1) {

    //Get Sensor Values
    _delay_ms(1);
    ////unsigned char leftTurnAvail = 0;
    //unsigned char rightTurnAvail = 0;
    //unsigned char straightAvail = 0;
    //char turnDirection;
    unsigned char checkSensorValue = get_QTR_value() & 0x07;// & 0x0F; //Only using B(3:0)
    PORTC = checkSensorValue; //allows to check if sensors are outputting correctly on C
    //	d0 = leftmost sensor
	  //  d1 = middle
	  //  d2 = rightmost Sensor

    //
    if(checkSensorValue == 0x01){
      leftmotor_forward();
      rightmotor_forward();
      _delay_ms(2);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    else if(checkSensorValue == 0x00){
      leftmotor_coast();
      rightmotor_forward();
      _delay_ms(2);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    else if(checkSensorValue == 0x04){
      leftmotor_forward();
      rightmotor_coast();
      _delay_ms(2);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    else if(checkSensorValue == 0x07){
      while(checkSensorValue != 0x01){
        leftmotor_reverse();
        rightmotor_forward();
        _delay_ms(2);
        leftmotor_brake();
        rightmotor_brake();
        _delay_ms(1);
        checkSensorValue = get_QTR_value() & 0x03;
      }
    }
}

  return 0;
}
