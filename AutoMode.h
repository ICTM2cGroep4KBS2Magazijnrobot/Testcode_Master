

#ifndef AutoMode_h
#define AutoMode_h
#include <Arduino.h>
#include "MotorControl.h"


//class AutoMode

class AutoMode {
    public:
        AutoMode(MotorControl motorA);
        void read();
        void autoMove(int encoderX, int encoderY);
        void Setup();
    private:
        MotorControl motorA;
        int _encoderY;
        int _encoderX;
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

void AutoMode::autoMove(int encoderY, int encoderX)
{
    Serial.println("AutoMode");


  
};

#endif