#define F_CPU 1000000UL
#include "motor.c"
#include "qtr_driver.c"


void driveforward();
void drivereverse();

int main() {
  init_motors ();
  init_QTR_driver();

  DDRC = 0xFF;

  while (1) {

    _delay_ms(1);

    unsigned char sensors = get_QTR_value() & 0x0F;

    PORTC = sensors;
    if(sensors == 0){
      driveforward();
    }
    else{ drivereverse(); }
  }

  return 1;
}

void driveforward(){

  leftmotor_forward();
  rightmotor_forward();

}

void drivereverse(){
  leftmotor_reverse();
  rightmotor_reverse();
}
