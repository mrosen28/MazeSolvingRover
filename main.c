#define F_CPU 1000000UL
#include "motor.c"
#include "qtr_driver.c"


void driveforward();
void turnLeft();
void turnRight();
void uturn();

int main() {
  //RoverSetup
  init_motors ();
  init_QTR_driver();

  DDRC = 0xFF;
  unsigned char checkSensorValue = get_QTR_value() & 0x0F;
  while (1) {

    //Get Sensor Values
    _delay_ms(1);
    checkSensorValue = get_QTR_value() & 0x0F; //Only using B(3:0)
    PORTC = checkSensorValue; //allows to check if sensors are outputting correctly on C
    //	d0 = rightmost sensor
	  //  d1 = right center sensor
	  //  d2 = left center sensor
	  //  d3 = left sensor

    if((checkSensorValue & 0x08) == 0){
      //Left Turn Available
      turnLeft();
      continue;
    }
    else if(checkSensorValue & 0x09 ){
      //No Left Turn
      driveforward();
      continue;
    }
    else if((checkSensorValue & 0x01) == 0){
      turnRight();
      continue;
    }
    else if(checkSensorValue & 0x0F){
      //Can Not Advance: uTurn
      uturn();
      continue;
    }
}

  return 1;
}

void driveforward(){
  unsigned char testSensorValue = get_QTR_value() & 0x06; //Check Center Sensors

  //StayOnLine
  if(!testSensorValue){
    //OnLine: Proceed
    leftmotor_forward();
    rightmotor_forward();
  }
  else if(testSensorValue == 0x02){
    //OffLine(RightSide): Compensating
    leftmotor_coast();
    rightmotor_forward();
  }
  else if(testSensorValue == 0x04){
    //OffLine(LeftSide): Compensating
    leftmotor_forward();
    rightmotor_coast();
  }

}

void uturn(){
  unsigned char checkSensorValue = get_QTR_value() & 0x0F;

  //While All Sensors Show Black, Turn Left
  while (checkSensorValue & 0x06){
    leftmotor_reverse();
    rightmotor_forward();
    checkSensorValue = get_QTR_value() & 0x0F;
  }
}

void turnLeft(){
  unsigned char checkSensorValue = get_QTR_value() & 0x0F;
  while((checkSensorValue & 0x08) == 0){
    leftmotor_reverse();
    rightmotor_forward();
    checkSensorValue = get_QTR_value() & 0x0F;
  }
  while (checkSensorValue & 0x06) {
    leftmotor_reverse();
    rightmotor_forward();
    checkSensorValue = get_QTR_value() & 0x0F;
  }
}

void turnRight(){
  unsigned char checkSensorValue = get_QTR_value() & 0x0F;
  while((checkSensorValue & 0x01) == 0){
    leftmotor_reverse();
    rightmotor_forward();
    checkSensorValue = get_QTR_value() & 0x0F;
  }
  while (checkSensorValue & 0x06) {
    leftmotor_reverse();
    rightmotor_forward();
    checkSensorValue = get_QTR_value() & 0x0F;
  }
}
