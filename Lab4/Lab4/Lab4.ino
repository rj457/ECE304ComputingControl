volatile float FIR_Co[3] = {1,-1.9021,1};
volatile int16_t FIR_CO_W[3] = {}; 
typedef int16_t fixed_point_t;
volatile int16_t x[101] = {818,818,818,614,409,205,205,409,409,409,409,409,409,409,205,205,409,614,818,818,818,818,818,614,409,205,205,409,409,409,409,409,409,409,205,409,409,614,818,818,818,818,818,614,409,409,205,409,409,409,409,409,409,409,205,409,409,614,818,818,818,818,818,614,409,205,205,409,409,409,409,409,409,409,205,409,409,614,818,818,818,818,818,614,409,205,205,409,409,409,409,409,409,409,205,409,409,614,818,818,818};
volatile int16_t y[101] = {};

int n;

void setup() {
  
  // put your setup code here, to run once:
  int16_t float_to_fixed(float input,int8_t fractional_bits);
  Serial.begin(2000000);
  //Serial.print(FIR_Co[1],4); 
  // initialize Timer5
  noInterrupts(); // disable all interrupts
  TCCR5A = 0;
  TCCR5B = 0;
  TIMSK5=0;
  TCNT5 = 0;
  
  OCR5A = 250; // compare match register 16MHz/256/0.004s=500Hz
  TCCR5B |= (1<<WGM52); // CTC mode
  TCCR5B |= (1<<CS52) | (0<<CS51) | (0<<CS50); // 256 prescaler
  TIMSK5 |= (1<<OCIE5A); // enable timer compare interrupt
  interrupts(); // enable all interrupts

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

void loop() {
   if (n == 101){
      noInterrupts();
      delay(1000);
      for (int j = 0;j<101;j++){
        delay(10);
        //fixed16_to_float(y[j],12)
        Serial.print(y[j]);
        Serial.println(" ");
        
      }
      n+=1;
   }
}

void ImplementX(){
  //convert FIR Coefficients to Fixed format 
  for (int i = 0;i<3;i++){
    float input = FIR_Co[i];
    int16_t input_float_size =12;
    int16_t f = float_to_fixed(input,input_float_size);
    FIR_CO_W[i] = f;
  }
}



//timer interrupt 
ISR(TIMER5_COMPA_vect){
  for (n = 2; n < 101; n++){
    y[n] = FIR_CO_W[0]*x[n] + FIR_CO_W[1]*x[n-1] + FIR_CO_W[2]*x[n-2];
    //Serial.print(y[n]);
  }
}
