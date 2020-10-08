int LED_pin = 13;
int Photocell_pin = A0;
int i = 0; 
float j = 0.0;
int k = 0;
float result;
int count = 0; 

int PWM = 0;
float voltage[128];

float voltage_inverse[] = {
0.0,
0.7,
1.2,
1.4,
1.8,
2,
2.2,
2.4,
2.6,
2.8,
2.9,
3.1,
3.2,
3.3,
3.4,
3.5,
3.6,
3.7,
3.8,
3.9,
4,
4.1,
4.2,
4.3,
4.4,
4.5};
int pwm_inverse[]={
0,
2,
4,
6,
8,
10,
12,
15,
18,
21,
24,
27,
32,
38,
40,
42,
49,
56,
64,
75,
86,
104,
123,
154,
186,
230};

float user_input_voltage = 0.0; 
int pwm_temp; 
float voltage_temp; 
float jk;

void setup() {
    Serial.begin(9600);
    pinMode(LED_pin, OUTPUT);
    pinMode(Photocell_pin, INPUT);
    Serial.println("---------new-------------");
    Serial.println(" ");
    for (jk = 0.0; jk <= 5.0; jk+=0.1){
      jk = round(jk*10.0) / 10.0;
      print_outvoltage(jk);
    }
//    store_to_LUT(); 
//    Serial.println("-------------------Inverse----------------------------");
//    inverse_table();
//    Serial.print(voltage_inverse[3]);
//    Serial.print(pwm_inverse[3]);
//    Serial.println(" "); 
    //Serial.println(voltage[24]);
//    cli();//stop interrupts
//
//    //set timer4 interrupt at 1Hz
//    TCCR4A = 0;// set entire TCCR1A register to 0
//    TCCR4B = 0;// same for TCCR1B
//    TCNT4  = 0;//initialize counter value to 0
//    // set compare match register for 1hz increments
//    OCR4A = 15624/1;// = (16*10^6) / (1*1024) - 1 (must be <65536)
//    // turn on CTC mode
//    TCCR4B |= (1 << WGM12);
//    // Set CS12 and CS10 bits for 1024 prescaler
//    TCCR4B |= (1 << CS12) | (1 << CS10);  
//    // enable timer compare interrupt
//    TIMSK4 |= (1 << OCIE4A);
//    sei();//allow interrupts
}
    
//ISR(TIMER4_COMPA_vect){
//  if (i == 128){
//    i = 0;  
//  }
//  analogWrite(LED_pin, i*2); // out put pwm as 2i
//  delay(500); //waiting 1s
//  int analog_val = analogRead(Photocell_pin); // read the analog after waiting 1s
//  float voltage_val  = analog_val * (5.0 / 1024.0);// convert to voltage
//  //inversetable[i].pwm = i; 
//  //inversetable[i].voltage = voltage_val; 
//  voltage[i] += voltage_val;
//  Serial.print(i*2); // prints value applied to LED
//  Serial.print(","); // comma for Excel field delineation
//  Serial.print(voltage_val); // prints voltage across bottom of voltage divider
//  Serial.println(" "); //*** must be last line for EXCEL ****
//  i = i + 1; 
//}

//void store_to_LUT(){
//  for (i=0;i<128;i++){
//    analogWrite(LED_pin, i*2); // out put pwm as 2i
//    delay(300); //waiting 1s
//    int analog_val = analogRead(Photocell_pin); // read the analog after waiting 1s
//    float voltage_val  = analog_val * (5.0 / 1024.0);// convert to voltage
//    //inversetable[i].pwm = i; 
//    //inversetable[i].voltage = voltage_val; 
//    voltage[i] += round(voltage_val*10.0) / 10.0;
//    Serial.print(i*2); // prints value applied to LED
//    Serial.print(","); // comma for Excel field delineation
//    Serial.print(voltage[i]); // prints voltage across bottom of voltage divider
//    Serial.println(" "); //*** must be last line for EXCEL ****
//  //i = i + 1; 
//  }
//}
//
//void inverse_table(){
//  for (j=0.00;j<4.90;j+=0.10){
//    count = 0;
//    PWM = 0;  
//    j = round(j*10.0) / 10.0; 
//    for (k=0;k<128;k++){
//      
//      if (j == voltage[k]){
//        count += 1; 
//        PWM += k*2;
////        Serial.print(j);
////        Serial.print(", ");
////        Serial.print(voltage[k]);
////        Serial.println(" ");
//      }
////      else{
////        continue; 
////      }
//    }
//    if (count == 0){
//      result = 0.0; 
//    }
//    else {
//      result = PWM / count; 
//      Serial.print(j);
//      Serial.print(", ");
//      Serial.print(result);
//      Serial.println(" ");
//    }
//  }
//}

void output_LUT(){
    analogWrite(LED_pin, pwm_temp); // out put pwm as 2i
    delay(1000); //waiting 1s
    int analog_val = analogRead(Photocell_pin); // read the analog after waiting 1s
    voltage_temp  = analog_val * (5.0 / 1024.0);// convert to voltage
    //inversetable[i].pwm = i; 
    //inversetable[i].voltage = voltage_val; 
//    voltage[i] += round(voltage_val*10.0) / 10.0;
//    Serial.print(i*2); // prints value applied to LED
//    Serial.print(","); // comma for Excel field delineation
//    Serial.print(voltage[i]); // prints voltage across bottom of voltage divider
//    Serial.println(" "); //*** must be last line for EXCEL ****
}

void print_outvoltage(float input){
    user_input_voltage = input; 
    for (int jj=0;jj<sizeof(voltage_inverse);jj++){
      if (user_input_voltage <= voltage_inverse[jj]){
        pwm_temp = (pwm_inverse[jj]+pwm_inverse[jj-1]) / 2;
        break; 
      }
    }
    output_LUT();
//    Serial.print("the user input voltage: ");
//    Serial.print(user_input_voltage);
//    Serial.println(" ");
//    Serial.print("the output voltage from LUT: ");
    Serial.print(round(voltage_temp*10.0)/10.0);
    Serial.println(" ");
}

void loop() {
  
}
