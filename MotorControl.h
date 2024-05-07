//Motor control header file
//See gitHub for changes
// Created by: Odin Adema

#ifndef MotorControl_h
#define MotorControl_h
#include <Arduino.h>
#include "Sensor.h"



//class MotorControl

class MotorControl {
    public:
        MotorControl(int Dir, int PWM, int Brake, int Tilt, int EncodeA, int EncodeB);
        void move(int richting, int snelheid);
        void read();
        void Sensorread();
        void stop();
    private:
        int _Dir;
        int _PWM;
        int _Brake;
        int _Tilt;
        int _EncodeA;
        int _EncodeB;
        Sensor _sensor = Sensor(_Tilt);

};

//constructor

MotorControl::MotorControl(int Dir, int PWM, int Brake, int Tilt, int EncodeA, int EncodeB) {
    _Dir = Dir;
    _PWM = PWM;
    _Brake = Brake;
    _Tilt = Tilt;
    _EncodeA = EncodeA;
    _EncodeB = EncodeB;
    _sensor = Sensor(_Tilt);
    pinMode(_Dir, OUTPUT);
    pinMode(_PWM, OUTPUT);
    pinMode(_Brake, OUTPUT);
};



//methodes

void MotorControl::read() 
{
    Serial.print("Motor Direction: ");
    Serial.print(_Dir);
    Serial.print(", Motor PWM: ");
    Serial.print(_PWM);
    Serial.print(", Motor Brake: ");
    Serial.println(_Brake);
};

void MotorControl::Sensorread()
{
    _sensor.read();
};

void MotorControl::move(int richting, int snelheid)
{
    if(richting == 0){
        //move motor to the left
       if (!_sensor.detectTilt()){
            digitalWrite(_Brake, LOW);
            analogWrite(_PWM, snelheid);
            digitalWrite(_Dir, LOW);
       } else {
              stop();
              
       }
    }else if (richting == 1){
        //move motor to the right
        if (!_sensor.detectTilt()){
            digitalWrite(_Brake, LOW);
            analogWrite(_PWM, snelheid);
            digitalWrite(_Dir, HIGH);
        } else {
            stop();
        }
    }else{
        //stop motor
        stop();
    }
};

void MotorControl::stop()
{
    digitalWrite(_Brake, HIGH);
    analogWrite(_PWM, 0);
};




#endif


