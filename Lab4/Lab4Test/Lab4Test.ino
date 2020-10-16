#include<FixedPoints.h>
#include<FixedPointsCommon.h>

typedef int16_t fixed_point_t;

void setup() {
  // put your setup code here, to run once:
  int16_t float_to_fixed(float input,int8_t fractional_bits);
  Serial.begin(9600);
  //setup the x[n]
  ImplementX();
}

inline int16_t float_to_fixed(float input,int16_t fractional_bits)
{
    return (int16_t)(round(input * (1 << fractional_bits)));
}
double fixed16_to_float(int16_t input, int16_t fractional_bits)
{
    return ((float)input / (float)(1 << fractional_bits));
}

void ImplementX(){
    SQ15x16 b[3] = {1,-1.9021,1};
    SQ15x16 f1 = 429;
    SQ15x16 f2 = 560;
    SQ15x16 f3 = 609;
    //b[1]*f1+b[2]*f4+b[3]*f3
    Serial.println(static_cast<double>(b[0]*f1+b[1]*f2+b[2]*f3));
//  int16_t f = float_to_fixed(1,0);
//  int16_t f1 = float_to_fixed(429,0); 
//  int16_t f2 = float_to_fixed(-1.9021,12);
//  int16_t f3 = float_to_fixed(609,0);
//  int16_t f4 = float_to_fixed(560,0);
//  int16_t f5 = fixed16_to_float(f*f1+f2*f4+f*f3,32);
//  Serial.print(f5); 
  //Serial.print(fixed16_to_float(f*f1,12));
//  Serial.print(fixed16_to_float(f*3,12));
}

void loop() {
  // put your main code here, to run repeatedly:

}
