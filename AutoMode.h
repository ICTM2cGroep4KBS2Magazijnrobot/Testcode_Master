

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
        void changeConfirmTrue();
        void changeConfirmFalse();
        bool homing(int encoderX, int encoderY, int X, int Y);
    private:
        MotorControl motorA;
        int _encoderY;
        int _encoderX;
        int X;
        int Y;
        bool verstuurConfirm = false;
        bool startcounter = false;

        int ArrayVakCords [5][5][2] ={
          {{0, 4550},{1470, 4550}, {2840, 4550}, {4270, 4550}, {5700, 4550}},   //rij0
          {{0, 3550},{1470, 3550}, {2840, 3550}, {4270, 3550}, {5700, 3550}},   //rij2
          {{0, 2550},{1470, 2550}, {2840, 2550}, {4270, 2550}, {5700, 2550}},   //rij3
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

void AutoMode ::changeConfirmTrue(){
  verstuurConfirm = true;
}
void AutoMode ::changeConfirmFalse(){
  verstuurConfirm = false;;
}

bool AutoMode::homing(int encoderX, int encoderY, int X, int Y){
  int  intXwaarde = ArrayVakCords[Y][X][0];
  int  intYwaarde = ArrayVakCords[Y][X][1];

  int cordoffset = 60;
  
  Wire.beginTransmission(0x08);
  Wire.write(0x10); //zet werken2 op true in slave
  Wire.endTransmission();

  //alles hieronder als de X EN Y waarde van encoder lager is dan gewilde x en y
  if(encoderX < intXwaarde - cordoffset){
    Wire.beginTransmission(0x08);
    Wire.write(0x66);
    Wire.endTransmission();
    return false;
//    Serial.println("X is te laag");
  }
  else{
    Wire.beginTransmission(0x08);
    Wire.write(0x67);
    Wire.endTransmission();
    return false;
  }
  if(encoderX > intXwaarde + cordoffset){
    Wire.beginTransmission(0x08);
    Wire.write(0x70);
    Wire.endTransmission();
    return false;
  }
  else{
    Wire.beginTransmission(0x08);
    Wire.write(0x71);
    Wire.endTransmission();
    return false;
  }
  if(encoderX < intXwaarde + cordoffset && encoderX > intXwaarde - cordoffset){
      if(encoderY < intYwaarde - cordoffset){
        Wire.beginTransmission(0x08);
        Wire.write(0x68);
        Wire.endTransmission();
        return false;
  }
  else{
    Wire.beginTransmission(0x08);
    Wire.write(0x69);
    Wire.endTransmission();
    return false;
  }
  if(encoderY > intYwaarde + cordoffset){
    Wire.beginTransmission(0x08);
    Wire.write(0x72);
    Wire.endTransmission();
    return false;
  }
  else{
    Wire.beginTransmission(0x08);
    Wire.write(0x73);
    Wire.endTransmission();
    return true;
  }
  }
  
}



void AutoMode::autoMove(int encoderX, int encoderY, int X, int Y){
  int intXwaarde;
  int intYwaarde;
  if(X != 9 && Y != 9){
      intXwaarde = ArrayVakCords[Y][X][0];
      intYwaarde = ArrayVakCords[Y][X][1];
  }
  else{
    intXwaarde = 8200;
    intYwaarde = 100;
  }

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

  if((encoderX < intXwaarde + cordoffset && encoderX > intXwaarde - cordoffset) && (encoderY < intYwaarde + cordoffset && encoderY > intYwaarde - cordoffset)){
      if(verstuurConfirm){
        verstuurConfirm = false;
        Serial.write('b');
        Serial.write(X);
        Serial.write(Y);
      }
  }

  
};

#endif
