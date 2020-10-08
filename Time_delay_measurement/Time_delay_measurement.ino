
void setup() {
    int LED_pin = 13;
    int Photocell_pin = A0;
    int data_count = 0;
    int data_collect_amount = 40; // how many measurements we're collecting per movement 
    float voltage_data_30[40]; // array for 30% PWM data
    float voltage_data_70[40]; // array for 70% PWM data
    unsigned long time; // variable to hold the amount of time that's passed
      
    Serial.begin(9600);
    pinMode(LED_pin, OUTPUT);
    pinMode(Photocell_pin, INPUT);
    delay(3000);
    
    // initially set the LED to 30% PWM
    Serial.println("___________at 30% pwm__________");
    analogWrite(LED_pin, 77); //30% of 255
    while (data_count < data_collect_amount){ 
        time = micros(); // check the amount of microseconds that have passed since the board started
        if (time % 250 == 0){ // because the arduino's resolution for the micros() function is 4 us, if the time is cleanly divisible by 250, that means 1000 us, or 1 ms, has passed  
            voltage_data_30[data_count] = analogRead(Photocell_pin)* (5.0 / 1024.0); // so, every 1 ms, measure the voltage
            data_count += 1;
        }
    }
    // print the data to excel
    for (int i = 0; i < data_collect_amount; i++){
        Serial.print(voltage_data_30[i]); 
        Serial.println(" "); //*** must be last line for EXCEL ****
    }
   
    Serial.println("___________at 70% pwm__________");
    data_count = 0;
    analogWrite(LED_pin, 179);//70% of 255
    while (data_count < data_collect_amount){
        time = micros();
        if (time % 250 == 0){ // every 1000 microseconds, because the arduino resolution for micros() is 4 microseconds
            voltage_data_70[data_count] =analogRead(Photocell_pin)* (5.0 / 1024.0);
            data_count += 1;
        }
    }
   // print the data to excel
    for (int i = 0; i < data_collect_amount; i++){
        Serial.print(voltage_data_70[i]); 
        Serial.println(" "); //*** must be last line for EXCEL ****
    }

    // switch back to 30%
    Serial.println("___________at 30% pwm__________");
    data_count = 0;
    analogWrite(LED_pin, 77);//30% of 255
    while (data_count < data_collect_amount){
        time = micros();
        if (time % 250 == 0){ // every 1000 microsecnds (1 ms)
            voltage_data_30[data_count] = analogRead(Photocell_pin)* (5.0 / 1024.0); 
            data_count += 1;
        }
    }
    // print the data to excel
    for (int i = 0; i < data_collect_amount; i++){
        Serial.print(voltage_data_30[i]); 
        Serial.println(" "); //*** must be last line for EXCEL ****
    }


}

void loop() {
    
}
