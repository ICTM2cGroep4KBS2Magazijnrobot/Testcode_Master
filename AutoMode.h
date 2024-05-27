

#ifndef AutoMode_h
#define AutoMode_h
#include <Arduino.h>
#include "MotorControl.h"
#include <Wire.h>

//class AutoMode

class AutoMode {
    public:
        AutoMode(MotorControl motorA);
        void read();
        void autoMove(int encoderX, int encoderY, int X, int Y);
        void Setup();
    private:
        MotorControl motorA;
        int _encoderY;
        int _encoderX;
        int X;
        int Y;
        
        int ArrayVakCords [5][5][2] ={
          {{0, 4450},{1470, 4450}, {2840, 4450}, {4270, 4450}, {5700, 4450}},   //rij0
          {{0, 3450},{1470, 3450}, {2840, 3450}, {4270, 3450}, {5700, 3450}},   //rij2
          {{0, 2450},{1470, 2450}, {2840, 2450}, {4270, 2450}, {5700, 2450}},   //rij3
          {{0, 1450},{1470, 1450}, {2840, 1450}, {4270, 1450}, {5700, 1450}},   //rij4
          {{0, 450},{1470, 450}, {2840, 450}, {4270, 450}, {5700, 450}}         //rij5
        };
};

//constructor

AutoMode::AutoMode(MotorControl _motorA) 
  : motorA(_motorA)
{
    Setup();
};

//methodes

void AutoMode::read() 
{



   
};

void AutoMode ::Setup()
{
    

    



};

void AutoMode::autoMove(int encoderX, int encoderY, int X, int Y){
  int  intXwaarde = ArrayVakCords[Y][X][0];
  int  intYwaarde = ArrayVakCords[Y][X][1];
//  Serial.println("Xwaarde :" + intXwaarde);
//  Serial.println("Yaarde :" + intYwaarde);
//
  int cordoffset = 60;
  
  Wire.beginTransmission(0x08);
  Wire.write(0x10); //zet werken2 op true in slave
  Wire.endTransmission();

  //alles hieronder als de X EN Y waarde van encoder lager is dan gewilde x en y
  if(encoderX < intXwaarde - cordoffset){
    Wire.beginTransmission(0x08);
    Wire.write(0x66);
    Wire.endTransmission();
//    Serial.println("X is te laag");
  }
  else{
    Wire.beginTransmission(0x08);
    Wire.write(0x67);
    Wire.endTransmission();
  }
  if(encoderX > intXwaarde + cordoffset){
    Wire.beginTransmission(0x08);
    Wire.write(0x70);
    Wire.endTransmission();
  }
  else{
    Wire.beginTransmission(0x08);
    Wire.write(0x71);
    Wire.endTransmission();
  }
//  if(encoderX > 
  if(encoderX < intXwaarde + cordoffset && encoderX > intXwaarde - cordoffset){
      if(encoderY < intYwaarde - cordoffset){
        Wire.beginTransmission(0x08);
        Wire.write(0x68);
        Wire.endTransmission();
  }
  else{
    Wire.beginTransmission(0x08);
    Wire.write(0x69);
    Wire.endTransmission();
  }
  if(encoderY > intYwaarde + cordoffset){
    Wire.beginTransmission(0x08);
    Wire.write(0x72);
    Wire.endTransmission();
  }
  else{
    Wire.beginTransmission(0x08);
    Wire.write(0x73);
    Wire.endTransmission();
  }
  }

 

//  Wire.endTransmission();


//Serial.println("Encoderx waarde is: " + encoderX);
//    if(encoderX > 2840){
//         motorA.move(0,255);
//    }

  
//  if(encoderX < wantedX){
//    while(encoderX < wantedX){
//      _motorA.move()
//    }
//  }
//  else if(encoderX > wantedX){
//    
//  }
//  while(encoderX < wantedX || encoderX > wantedX)
//    //Serial.println("AutoMode");
  

  
};

#endif
