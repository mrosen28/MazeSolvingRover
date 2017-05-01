#define F_CPU 1000000UL
#include "motor.c"
#include "qtr_driver.c"

int main() {
  //RoverSetup
  init_motors ();
  init_QTR_driver();

  DDRC = 0xFF;

  while (1) {

    unsigned char checkSensorValue = get_QTR_value() & 0x03;// & 0x0F; //Only using B(3:0) "***-----"

    if(checkSensorValue == 0x02){ //black on left, white on right
      leftmotor_forward();
      rightmotor_forward();
      _delay_ms(2);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    else if(checkSensorValue == 0x00){//white on both
      leftmotor_coast();
      rightmotor_forward();
      _delay_ms(2);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    else if(checkSensorValue == 0x03){//black on both
      leftmotor_forward();
      rightmotor_reverse();
      _delay_ms(2);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    else if(checkSensorValue == 0x01){ //white on left, black on right
        leftmotor_forward();
        rightmotor_coast();
        _delay_ms(2);
        leftmotor_brake();
        rightmotor_brake();
        _delay_ms(1);

      }
    }


  return 0;
}
