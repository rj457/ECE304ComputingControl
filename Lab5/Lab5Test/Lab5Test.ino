//#include <ServoTimer2.h>
#include <Servo.h>
//ServoTimer2 servo1;
Servo myservo;

int pos = 0; 
int potPin = 0; 
int voltage = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(10);
  myservo.write(0); 
  delay(3000); //hold for three seconds at 0 degree
  bandwidthtest();
//timer based interrupt
//  noInterrupts(); // disable all interrupts
//  TCCR3A = 0;// set entire TCCR1A register to 0
//  TCCR3B = 0;// same for TCCR1B
//  TIMSK3 = 0;
//  TCNT3  = 0;//initialize counter value to 0
//  // set compare match register for 1hz increments
//  OCR3A = 1562;// = (16*10^6) / (10*1024) - 1 (must be <65536)
//  // turn on CTC mode
//  TCCR3B |= (0 << WGM32)|(0 << WGM31)|(0 << WGM30);
//  // Set CS12 and CS10 bits for 1024 prescaler
//  TCCR3B |= (1 << CS32) | (0 << CS31)|(1 << CS30);  
//  // enable timer compare interrupt
//  TIMSK3 |= (1 << OCIE3A);
//  interrupts(); // enable all interrupts
}

void loop() {
  
}

void bandwidthtest(){
  for (pos = 0; pos <= 170; pos += 2) { // goes from 0 degrees to 170 degrees
    //in step of 2 increment
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(12);    // give a totoal of 2.9 s to finish the loop
    voltage = analogRead(potPin); 
    Serial.print(pos);
    Serial.print(", ");
    Serial.print(voltage);
    Serial.println(" "); 
    delay(25); 
  }
}
