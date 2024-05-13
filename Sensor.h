//sensor header file
//See gitHub for changes
// Created by: Odin Adema

#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include "Timer.h"
#include "Button.h"

//class Sensors

class Sensor {
    public:
        Sensor(int Tilt);
        void read();
        bool detectTilt();
        
    private:
        int _Tilt;
        bool state = LOW;
        bool previousState = LOW;
        Button button = Button(_Tilt);
        
};

//constructor

Sensor::Sensor(int Tilt) {
    _Tilt = Tilt;
    pinMode(_Tilt, INPUT_PULLUP);
    button = Button(_Tilt);
};

void Sensor::read() 
{
    int detectTilt = button.getState();
    Serial.print("Sensor Tilt: ");
    Serial.println(detectTilt);
};

bool Sensor::detectTilt()
{
    
    state = button.getState();

    switch (state)
    {
    case LOW:
        return false;
        break;
    case HIGH:
        return true;
        break;
    
    default:
        return false;
        break;
    }
};



#endif
