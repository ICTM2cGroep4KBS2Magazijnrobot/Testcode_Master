

#ifndef AutoMode_h
#define AutoMode_h
#include <Arduino.h>
#include "MotorControl.h"
#include <Wire.h>

boolean geprikt = false;

//class AutoMode
boolean Picking = true;
boolean omhoog = false;
//int Pickingfase = 1;

enum fase{voren, achter, lift, bevestigen, DEfault};
fase Pickingfase = DEfault;

class AutoMode {
    public:
        AutoMode(MotorControl motorA);
        void read();
        void autoMove(int encoderX, int encoderY, int X, int Y);
        void Setup();
        void changeConfirmTrue();
        void changeConfirmFalse();
        void setfase();
        bool homing(int encoderX, int encoderY, int X, int Y);
    private:
        enum fase{voren, achter, lift, bevestigen, Default};
        fase Pickingfase = Default;
//        unsigned char Pickingfase;

        MotorControl motorA;
        int _encoderY;
        int _encoderX;
        int X;
        int Y;
        bool verstuurConfirm = false;

        int ArrayVakCords [5][5][2] ={
          {{0, 4770},{1470, 4770}, {2840, 4770}, {4270, 4770}, {5700, 4770}},   //rij0
          {{0, 3670},{1390, 3670}, {2760, 3670}, {4190, 3670}, {5620, 3670}},   //rij2
          {{0, 2720},{1470, 2720}, {2840, 2720}, {4270, 2720}, {5700, 2720}},   //rij3
          {{0, 1650},{1470, 1650}, {2840, 1650}, {4270, 1650}, {5700, 1650}},   //rij4
          {{0, 650},{1470, 650}, {2840, 650}, {4270, 650}, {5700, 650}}         //rij5
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

  int cordoffset = 40;
  
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


void AutoMode::setfase(){
  Pickingfase = voren;
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
  int cordoffset = 100;

  if (omhoog == false){
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
  }
  //check of je in het vakje zit
  if((encoderX < intXwaarde + cordoffset && encoderX > intXwaarde - cordoffset) && (encoderY < intYwaarde + cordoffset && encoderY > intYwaarde - cordoffset)){
    if(Picking){
      if(verstuurConfirm){
           int distance = motorA.getDistance();
      switch(Pickingfase){
        case voren:
          Serial.write('c');
          Serial.write(5);
          if(distance < 16){
            motorA.move(0, 255); 

          }
          else{
            motorA.stop();
            Pickingfase = lift;
          }
          break;
        case lift:
        omhoog = true;
//        cordoffset = 100;
          if(encoderY < (intYwaarde + 35)){
              Wire.beginTransmission(0x08);
              Wire.write(0x68);
              Wire.endTransmission();
          }
          else{     
              omhoog = false;
              Pickingfase = achter;
              
          }
          break;    
        case achter:
          if(distance >= 6){
            motorA.move(1,255);  
          }
          else{
            motorA.stop();
            Pickingfase = bevestigen;
            Serial.write('c');
            Serial.write(2);
          }
          break;
        case bevestigen:
          if(verstuurConfirm){
            verstuurConfirm = false;
            
            Serial.write('b');
            Serial.write(X);
            Serial.write(Y);
          }
          break;
         case DEfault:
          Pickingfase = voren;
          break;
      }
      }
    }
  }

  
};

#endif
