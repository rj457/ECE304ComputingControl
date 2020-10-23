#include<FixedPoints.h>
#include<FixedPointsCommon.h>

SQ15x16 FIR_Co[3] = {1,-1.9021,1};
typedef int16_t fixed_point_t;
//New Quants Table
SQ15x16 x[101] = {609,560,429,257,98,-5,-29,17,98,171,200,171,98,17,-29,-5,
98,257,429,560,609,560,429,257,98,-5,-29,17,98,171,200,171,98,17,-29,-5,98,257,429,560,
609,560,429,257,98,-5,-29,17,98,171,200,171,98,17,-29,-5,98,257,429,560,609,560,429,257,
98,-5,-29,17,98,171,200,171,98,17,-29,-5,98,257,429,560,609,560,429,257,98,-5,-29,17,98,
171,200,171,98,17,-29,-5,98,257,429,560,609};

SQ15x16 y[101] = {};

int n;

void setup() {
  
  // put your setup code here, to run once:
  int16_t float_to_fixed(float input,int16_t fractional_bits);
  Serial.begin(2000000);
  
  noInterrupts(); // disable all interrupts
  TCCR5A = 0;
  TCCR5B = 0;
  TIMSK5=0;
  TCNT5 = 0;
  
  OCR5A = 500; // compare match register 16MHz/256/0.004s=500Hz
  TCCR5B |= (1<<WGM52); // CTC mode
  TCCR5B |= (1<<CS52) | (0<<CS51) | (0<<CS50); // 256 prescaler
  TIMSK5 |= (1<<OCIE5A); // enable timer compare interrupt
  interrupts(); // enable all interrupts
}
void loop() {
   if (n == 101){
      noInterrupts();
      delay(1000);
      for (int j = 0;j<101;j++){
        delay(10);
        Serial.print(static_cast<double>(y[j]));
        Serial.println(" ");
      }
      n+=1;
   }
}

//timer interrupt 
ISR(TIMER5_COMPA_vect){
  for (n = 2; n < 101; n++){
    y[n] = static_cast<double>(FIR_Co[0]*x[n] + FIR_Co[1]*x[n-1] + FIR_Co[2]*x[n-2]);
  }
}
