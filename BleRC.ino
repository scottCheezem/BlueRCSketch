#include <SPI.h>
#include <ble.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h>


#define MIN_THRESHOLD 50

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *m1 = AFMS.getMotor(1);
Adafruit_DCMotor *m2 = AFMS.getMotor(2);
Adafruit_DCMotor *m3 = AFMS.getMotor(3);
Adafruit_DCMotor *m4 = AFMS.getMotor(4);

byte xVal;
byte xMag;
byte yVal;
byte yMag;



boolean connected;

void setup() {
  
  AFMS.begin();
  
  
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
    

    
    
    //magnituted are either 1 for positive direction, 0 for negetive direction...
    
    
    if(xVal = ble_read()){
      xMag = ble_read();
      yVal = ble_read();
      yMag = ble_read();
      
        
      
      
     //Serial.print("buf:");
     //Serial.print(xVal);
     //Serial.print(",");
     //Serial.print(xMag);
     //Serial.print(",");
     //Serial.print(yVal);
     //Serial.print(",");
     //Serial.print(yMag);
     //Serial.println(";");
     
     doTheMath();
     
    }
    
    

    
  }
  /*for delivering data back to device
  if(digitalRead(4) == LOW){
      //Serial.println("HI");
       ble_write('1'); 
    }
  */
  
  // Allow BLE Shield to send/receive data
  ble_do_events();
  //digitalWrite(RED, LOW);
  //delay(10);
}


void setConnected(boolean newState){
  if(newState != connected){
    connected = newState;
    if(connected){
      //Serial.println("Now Connected");
      //turn on an LED
    }else{
      //Serial.println("Now Disconnected");
      allStop();
      //turn off an LED
    }
  }
  
}

void doTheMath(){
  int lSpeed;
  int rSpeed;
  
  if(xVal == 0 && yVal == 0){
    //Serial.println("Stopping");
   allStop();
   delay(100);
   return; 
    
  }
  
  
  

  if(xMag == 0){
   //turning to the left
   //so right motors faster than left
   //Serial.println("to the left");
   lSpeed = lSpeed*xVal;
    
  }else if(xMag == 1){
   //turning to the right
   //left > right
   rSpeed = rSpeed*xVal;
   //Serial.println("to the right");
  }
  
  // 
  if(yMag == 0){
   //backwards 
   //Serial.print("backwards, ");

   lSpeed = -255*yVal;
   rSpeed = -255*yVal;
   
   setLeftSpeed(lSpeed);
   setRightSpeed(rSpeed);
   
   m1->run(BACKWARD);
   m2->run(BACKWARD);
   m3->run(BACKWARD);
   m4->run(BACKWARD);
   
   
  }
  
  else if(yMag == 1){
   //forwards 
   //Serial.print("forward, "); 
   
   lSpeed = 255*yVal;
   rSpeed = 255*yVal;
   
   setLeftSpeed(lSpeed);
   setRightSpeed(rSpeed);
   
   m1->run(FORWARD);
   m2->run(FORWARD);
   m3->run(FORWARD);
   m4->run(FORWARD);
   
   
   
   
  }
  
  
  
  //delay(100);
  
}



void allStop(){
 m1->setSpeed(0);
 m2->setSpeed(0);
 m3->setSpeed(0);
 m4->setSpeed(0);

 m1->run(RELEASE);  
 m2->run(RELEASE);
 m3->run(RELEASE);
 m4->run(RELEASE);

}

void setLeftSpeed(int s){
  //m1 and m4
  m1->setSpeed(s);
  m4->setSpeed(s);
  
  
  
}

void setRightSpeed(int s){
  m3->setSpeed(s);
  m2->setSpeed(s);
  //m3 and m2
  
}

