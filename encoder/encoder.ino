/*
 * DC Motor Control with Arduino and MotorShield
 * Using one PC6-C-4 decoder circuit board (LS7184 chip) and one interrupt pin
 % Need 12 V external power supply
 * 
 * October 4, 2009 (v. 1.3)
 */

//#include <AFMotor.h>                // motorshield library

//AF_DCMotor motor(2, MOTOR12_2KHZ); // create motor #2, 2KHz pwm
// Double check that the motor number matches your motor shield's setup

#define ClockPin 2      // clock interrupt pin
#define UpDownPin 12    // direction pin
int encoder0Pos = 0;  // encoder position
int count = 0;
int updown = 0;
unsigned long time_1, time_2, dt;



long setPoint = 0;
int error = 0;


void setup() {
  Serial.begin(9600);            // set up Serial library at 9600 bps

  
  pinMode(ClockPin, INPUT);
  pinMode(UpDownPin, INPUT); 

// encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoder, CHANGE);
  time_1 = millis();              // read the initial time stamp
}

void loop() {
  // Serial.println("Motor Control");
  time_2 = millis();              // read the current time stamp
  dt = time_2 - time_1;           // compute delta time
  time_1 = time_2;                // reassign new time_1
  
  //*** Remeber time is in milliseconds!!!
  
  // update state variables for use in PID controller

  error = (int)(setPoint - encoder0Pos);             // position error in counts
  

  // setspeed only takes positive values and a direction.
  // this takes care of the bookkeeping
//  if (error > 0 && error < 800)
//  {
//    motor.setSpeed(30);
//    motor.run(FORWARD);
//  }
//  else if ( error > 800)
//  {
//    motor.setSpeed(30);
//    motor.run(BACKWARD);
//  }
  
//  Serial.print(time_2, DEC);           // print out time since the beginning in ms
//  Serial.print(" ");                   // space separator
//  Serial.println(error, DEC);   // print out the encoder position

Serial.println(encoder0Pos);

  // Adjust here if you want to print out additional variables.
  // Remeber what you printed when you go to matlab!


}
// Interrupt routine
void doEncoder(){
  count = digitalRead(ClockPin);       // read x4 clock output
  updown = digitalRead(UpDownPin);     // read the direction of motor
  if (count == HIGH) {                  // a pulse is detected 
    if (updown == HIGH) {              // cw direction
      encoder0Pos = encoder0Pos + 1;   // increment motor position
    }
    else {                              // ccw direction
      encoder0Pos = encoder0Pos - 1;    // decrement motor position
    }
  }
}
 
