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
        
};

//constructor

Sensor::Sensor(int Tilt) {
    _Tilt = Tilt;
    pinMode(_Tilt, INPUT);
};

void Sensor::read() 
{
    int detectTilt = digitalRead(_Tilt);
    Serial.print("Sensor Tilt: ");
    Serial.print(detectTilt);
};

bool Sensor::detectTilt() {
    int detectTilt = digitalRead(_Tilt);
    if (detectTilt == HIGH) {
        return true;
    }
    else {
        return false;
    }
};



#endif
