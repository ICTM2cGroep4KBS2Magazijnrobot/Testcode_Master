//Motor control header file
//See gitHub for changes
// Created by: Naweed Noori

#ifndef MotorControl_h
#define MotorControl_h
#include <Arduino.h>
#include <Wire.h>
#include "Sensor.h"



//class MotorControl

class MotorControl {
    public:
        MotorControl(int Dir, int PWM, int Tilt, int EncodeA, int EncodeB);
        void move(int richting, int snelheid);
        void read();
        bool Sensorread();
        void stop();
        void connection_Tilt();
        void readData(int richting, int snelheid);

    private:
        int _Dir;
        int _PWM;
        int _Tilt;
        int _EncodeA;
        int _EncodeB;
        Sensor _sensor = Sensor(_Tilt);

};

//constructor

MotorControl::MotorControl(int Dir, int PWM, int Tilt, int EncodeA, int EncodeB) {
    _Dir = Dir;
    _PWM = PWM;
    _Tilt = Tilt;
    _EncodeA = EncodeA;
    _EncodeB = EncodeB;
    _sensor = Sensor(_Tilt);
    pinMode(_Dir, OUTPUT);
    pinMode(_PWM, OUTPUT);
};



//methodes

void MotorControl::read() 
{
//    Serial.print("Motor Direction: ");
//    Serial.print(_Dir);
//    Serial.print(", Motor PWM: ");
//    Serial.println(_PWM);
};

void MotorControl::readData(int richting, int snelheid) 
{
    // Serial.print("Motor Direction: ");
    // Serial.print(richting);
    // Serial.print(", Motor PWM: ");
    // Serial.println(snelheid);
};

bool MotorControl::Sensorread()
{
    _sensor.read();
};

void MotorControl::move(int richting, int snelheid)
{
connection_Tilt();
    if(richting == 0){
        //move motor to the left
       if (_sensor.detectTilt()){
            analogWrite(_PWM, snelheid);
            digitalWrite(_Dir, LOW);
       } else {
              stop();
              
       }
    }else if (richting == 1){
        //move motor to the right
        if (_sensor.detectTilt() || !_sensor.detectTilt()){
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
    analogWrite(_PWM, 0);
};

void MotorControl::connection_Tilt()
{
    // Send the data to the Slave
    if (!_sensor.detectTilt())
    {
        Wire.beginTransmission(0x08);
        Wire.write(0x10);
        Wire.endTransmission();
    }
    else if (_sensor.detectTilt())
    {
        Wire.beginTransmission(0x08);
        Wire.write(0x20);
        Wire.endTransmission();
    }
}




#endif
