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
        MotorControl(int Dir, int PWM, int Brake, int Tilt, int EncodeA, int EncodeB);
        void move(int richting, int snelheid);
        void read();
        void Sensorread();
        void stop();
        void connection_Tilt();

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
       if (_sensor.detectTilt()){
            digitalWrite(_Brake, LOW);
            analogWrite(_PWM, snelheid);
            digitalWrite(_Dir, LOW);
       } else {
              stop();
              
       }
    }else if (richting == 1){
        //move motor to the right
        if (_sensor.detectTilt() || !_sensor.detectTilt()){
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

void MotorControl::connection_Tilt()
{
    // Send the data to the Slave
    if (!_sensor.detectTilt())
    {
        Serial.print(": Sending 16");
        Wire.beginTransmission(0x08);
        Wire.write(0x10);
        Wire.endTransmission();
    }
    else if (_sensor.detectTilt())
    {
        Serial.print(": Sending 32");
        Wire.beginTransmission(0x08);
        Wire.write(0x20);
        Wire.endTransmission();
    }
}




#endif


