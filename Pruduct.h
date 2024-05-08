
#ifndef Doos_h
#define Doos_h
#include <Arduino.h>



class Pruduct {
  private:
    int _pin;
    int _pin2;
    
  public:
    Pruduct(int pin, int pin2);
    void read();
    int getCoordinaatX();
    int getCoordinaatY();
};
Pruduct::Pruduct(int pin, int pin2) 
{
_pin = pin;
_pin2 = pin2;

}

void Pruduct::read() 
{
    Serial.print("Doos: x= ");
    Serial.print(_pin);
    Serial.print(" : y= ");
    Serial.println(_pin2);

}

int Pruduct::getCoordinaatX() 
{
  if(_pin <= 4 && _pin >= 0){
    Serial.print("Doos: x= ");
    Serial.println(_pin);
    return _pin;
  }else{
    Serial.println("Deze waarde is niet geldig");
    return -1;
  }
}

int Pruduct::getCoordinaatY() 
{
  if(_pin2 <= 4 && _pin2 >= 0){
    Serial.print("Doos: y= ");
    Serial.println(_pin2);
    return _pin2;
  }else{
    Serial.println("Deze waarde is niet geldig");
    return -1;
  }
}


#endif