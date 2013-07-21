#include <SPI.h>
#include <ble.h>

#define RED 3

void setup() {
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
    
    
    
    
    byte led;
    byte val;
    
    if(led = ble_read()){
      //read the first number for the led to address, and the second for the value...

     val = ble_read();

      analogWrite(led, val);
      Serial.print(led);
      Serial.print(":");
      Serial.print(val);
      Serial.print("\n");
      
      
    }
    
    

    
  }
  if(digitalRead(4) == LOW){
      Serial.println("HI");
       ble_write('1'); 
    }
  
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
