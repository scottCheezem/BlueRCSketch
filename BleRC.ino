#include <SPI.h>
#include <ble.h>


int pwm_a = 3;  //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //dir control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //dir control for motor outputs 3 and 4 is on digital pin 13




void setup() {
  
  
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
  
  
  analogWrite(pwm_a, 0);
  analogWrite(pwm_b, 0);
  
  // put your setup code here, to run once:
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();

  ble_begin();

  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly: 


  if(ble_connected()){
    digitalWrite(7,255); 

  }  

   

  
  while(ble_available()){
    
    
    
    
    //byte motor1;
    byte valForMotor1;
    byte dirForMotor1;
    
    //byte motor2;
    byte valForMotor2;
    byte dirForMotor2;
    
    if(valForMotor1 = ble_read()){
      //read the first number for the led to address, and the second for the value...

     dirForMotor1 = ble_read();
     
     valForMotor2 = ble_read();
     dirForMotor2 = ble_read();
     
     digitalWrite(dir_a, dirForMotor1);
     analogWrite(pwm_a, valForMotor1);
     
     digitalWrite(dir_b, dirForMotor2);
     analogWrite(pwm_b, valForMotor2);
    

     Serial.print("valForMotor1:");     
     Serial.println(valForMotor1);
     
     Serial.print("dirForMotor1:");     
     Serial.println(dirForMotor1);

      
     Serial.print("valForMotor2:");     
     Serial.println(valForMotor2);
     
     Serial.print("dirForMotor2:");     
     Serial.println(dirForMotor2);

      Serial.println("-----");


    }
    
    

    
  }
  /*
  if(digitalRead(4) == LOW){
      Serial.println("HI");
       ble_write('1'); 
    }
  */
  if (!ble_connected())
  {
    digitalWrite(7, LOW);

    //analog_enabled = false;
    //digitalWrite(DIGITAL_OUT_PIN, LOW);
  }
  
  // Allow BLE Shield to send/receive data
  ble_do_events();
  //digitalWrite(RED, LOW);
}
