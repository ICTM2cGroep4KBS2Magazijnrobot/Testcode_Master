

#ifndef AutoMode_h
#define AutoMode_h
#include <Arduino.h>
#include "MotorControl.h"


//class AutoMode

class AutoMode {
    public:
        AutoMode(MotorControl motorA);
        void read();
        void autoMove();
    private:
        MotorControl motorA;
        int _xValue;
        int _yValue;
        int _state;
};

//constructor

AutoMode::AutoMode(MotorControl _motorA) 
  : motorA(_motorA)
{


};

//methodes

void AutoMode::read() 
{

   
};

void AutoMode::autoMove()
{
    Serial.println("AutoMode");


  
};

#endif