//Joystick header file
//See gitHub for changes
//Created by: Odin Adema && Naweed Noori

#ifndef Joystick_h
#define Joystick_h
#include <Arduino.h>
#include "MotorControl.h"

//class Joystick

class Joystick {
    public:
        Joystick(int xPin, int yPin, int pressPin, MotorControl motorA);
        void manualMove(bool state);
        void read();
    private:
        MotorControl motorA;
        int _xPin;
        int _yPin;
        int _pressPin;
        int _xValue;
        int _yValue;
        int _state;
        

};

//constructor

Joystick::Joystick(int xPin, int yPin, int pressPin, MotorControl _motorA) 
  : motorA(_motorA), _xPin(xPin), _yPin(yPin), _pressPin(pressPin)
{
    pinMode(_xPin, INPUT);
    pinMode(_yPin, INPUT);
    pinMode(_pressPin, INPUT_PULLUP);
};

//methodes

void Joystick::read() 
{

    int JoyX = analogRead(_xPin);
    int JoyY = analogRead(_yPin);
    int JoyPress = digitalRead(_pressPin);

//    Serial.print("Joystick X: ");
//    Serial.print(JoyX);
//    Serial.print(", Joystick Y: ");
//    Serial.print(JoyY);
//    Serial.print(", Joystick Press: ");
//    Serial.println(JoyPress);
};

void Joystick::manualMove(bool state)
{
    int JoyX = analogRead(_xPin);
    int JoyY = analogRead(_yPin);
    int JoyPress = digitalRead(_pressPin);

    if(state == 0){

    if(JoyX >= 550){
        int MotorXhoog = map(JoyX, 550, 1023, 0, 255);
        motorA.move(1, MotorXhoog);

        
    }else if(JoyX <= 460){
        int MotorXlaag = map(JoyX, 0, 460, 255, 0);
        motorA.move(0, MotorXlaag);
       
       
    }else{
        motorA.move(2, 0);
    }
    }else{
        motorA.stop();
    }
};




#endif
