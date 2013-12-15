#include <SPI.h>
#include <ble.h>

#include <AFMotor.h>

AF_DCMotor RightFrontMotor(1);
AF_DCMotor LeftFrontMotor(2);
AF_DCMotor LeftBackMotor(3);
AF_DCMotor RightBackMotor(4);

boolean connected;

void setup() {
  
  
  
  
  // put your setup code here, to run once:
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();

  ble_begin();

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly: 

/*
  if(ble_connected()){
    //set some sort of pin as verification we connected.  but only once

  }  */
  
  setConnected(ble_connected());
   

  //read in an x,y value over ble...
  while(ble_available()){
    
    
//[xy]Mag : magnitude for the x or y axis, 0-100
//[xy]Sign : the direction 1 positive, 0 for negative along the axis        
//buf[]={xMag,xSign,yMag,ySign, NULL}
    

    byte xVal;
    byte xMag;
    byte yVal;
    byte yMag;
    
    
    
    
    if(xVal = ble_read()){
      xMag = ble_read();
      yVal = ble_read();
      yMag = ble_read();
      
     Serial.print("buf:");
     Serial.print(xVal);
     Serial.print(",");
     Serial.print(xMag);
     Serial.print(",");
     Serial.print(yVal);
     Serial.print(",");
     Serial.print(yMag);
     Serial.println(";");
     
     
     
    }
    
    

    
  }
  /*for delivering data back to device
  if(digitalRead(4) == LOW){
      Serial.println("HI");
       ble_write('1'); 
    }
  */
  
  // Allow BLE Shield to send/receive data
  ble_do_events();
  //digitalWrite(RED, LOW);
}


void setConnected(boolean newState){
  if(newState != connected){
    connected = newState;
    if(connected){
      Serial.println("Now Connected");
      //turn on an LED
    }else{
      Serial.println("Now Disconnected");
      //turn off an LED
    }
  }
  
}

