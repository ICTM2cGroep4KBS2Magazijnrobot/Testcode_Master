//Motor control header file
//See gitHub for changes
// Created by: Naweed Noori

#ifndef MotorControl_h
#define MotorControl_h
#define sensor A3
#include <Arduino.h>
#include <Wire.h>
#include "Sensor.h"



//class MotorControl

class MotorControl {
    public:
        MotorControl(int Dir, int PWM, int Tilt, int EncodeA, int EncodeB);
        void move(int richting, int snelheid);
        void read();
        void stop();
        void connection_Tilt();
        void connection_IR();
        void readData(int richting, int snelheid);
        bool Sensorread();
        int getDistance();

    private:
        int _Dir;
        int _PWM;
        int _Tilt;
        int _EncodeA;
        int _EncodeB;
        int distance;
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

int MotorControl::getDistance() // MAX 16 cm MIN 6 cm
{
    float volts = analogRead(sensor)*0.0048828125;  // Gevonden op internet. value from sensor * (5/1024)
    int distance = 13*pow(volts, -1); // Gevonden op internet. Is een formule om de afstand te berekenen en komt uit de datasheet
    return distance;
};

void MotorControl::move(int richting, int snelheid)
{
connection_Tilt();
connection_IR();
    if(richting == 0){
        //move motor to the left / Naar voren
       if (_sensor.detectTilt() && (getDistance() >= 6 && getDistance() < 16)) { // 16 is het maximum en 6 is het minimum
            analogWrite(_PWM, snelheid);
            digitalWrite(_Dir, LOW);
       }
       else {
            stop();  
       }
    }else if (richting == 1){
        //move motor to the right / Naar achteren
        if (getDistance() >= 7 && (_sensor.detectTilt() || !_sensor.detectTilt())){ // 16 is het maximum en 6 is het minimum
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

void MotorControl::connection_IR()
{
    if (getDistance() <= 7) // Wel bewegen op x en y
    {
        Wire.beginTransmission(0x08);
        Wire.write(0x81);
        Wire.endTransmission();
    }
    else if (getDistance() >= 8) // Niet bewegen op x en y
    {
        Wire.beginTransmission(0x08);
        Wire.write(0x82);
        Wire.endTransmission();
    }
    
}




#endif
