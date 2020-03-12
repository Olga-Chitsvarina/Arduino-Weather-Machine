
#include <CheapStepper.h>

CheapStepper stepper;
// 8 <--> IN1
// 9 <--> IN2
// 10 <--> IN3
// 11 <--> IN4

int potPin = 0;    //potentiometer pin
int val = 0;       //reading from potentiometer

void setup() {
  
  Serial.begin(9600);
}

void loop() {
    
    //Read Potentiometer
    val = analogRead(potPin);

    //Map the reading to 0~23 corresponding to 24 hours of the day
    val = map(val, 0, 747, 0, 23);
    if(val > 24){val = 23;}
    //Map the reading to 0~4096 corresponding to the rotation of the motor
    val = map(val, 0, 23, 0, 4095);
    if(val > 4095){val = 4095;}

    //Get current location of motor
    int current = (int)stepper.getStep();

    //Move the motor to match the value
    if(current < val){
      stepper.stepCW(); 
      //counter--;
    }
    else if(current > val){
      stepper.stepCCW();
    }
    else{
      };

  }

/* REFERENCES 
 *  1) Cheap Stepper 
 *  https://github.com/tyhenry/CheapStepper
 *  2) Stepper Speed Control
 *  https://www.arduino.cc/en/tutorial/stepperSpeedControl
 *  3) Stepper Motors with Arduino.
 *  https://www.youtube.com/watch?time_continue=1033&v=0qwrnUeSpYQ&feature=emb_logo
*/
