// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"
#include "MotorControl.h"
#include "AutoMode.h"
//#include "Pruduct.h"
const unsigned long PING_INTERVAL = 5000; 
const unsigned long PING_TIMEOUT = 4000;  

    unsigned long lastPingTime;
    bool waitingForPong;
    int lastSentPing;

int redPin = 4;
int greenPin = 5;

int lastClkState = HIGH;
int counter = 0;
bool sensorX = false;

const int CLK_PIN = 2;
const int DT_PIN = 7;

MotorControl motorA(12, 3, 6,2,7); 

Joystick joystick(A2, 0, 0, motorA);

AutoMode automode(motorA);

Button button(10);
Button noodstop(8);
Button modus(9);

bool state = LOW;
bool state2 = LOW;
bool state3 = LOW;
bool previousState = LOW;
bool previousState2 = LOW;
bool previousState3 = LOW;
bool start = true;

bool werken = true;
bool Auto = false;
bool noodstopState = false;
bool modusState = false;
bool sensorY = true; // Voeg deze regel toe aan het begin van je code

bool werkenPressed = false;
bool noodstopPressed = false;
bool green = false;

int startupX = 0;
int startupY = 4;

int incomingX = 0;
int incomingY = 4;

bool veranderCoords = true;
bool changeX = true;
bool changeY = true;
boolean stap = true;
bool XofY = true;

String receivedString = "";
String incomingString = "";
byte incomingByte = 0;
int incomingEncoderX = 0;

int beweegCounter = 0;
int oudeX = 0;
int oudeY = 0;



enum ButtonState {
    Modus,
    AanUit,
    Noodstop,
    NoodstopReleased,
    Default
};


void setup() {
    attachInterrupt(digitalPinToInterrupt(CLK_PIN), handleEncoder, CHANGE);

        //initialize the I2C communication as master
        Wire.begin();
    
        Serial.begin(115200);
        pinMode(redPin, OUTPUT);
        pinMode(greenPin, OUTPUT);
//        automode.changeConfirmFalse();

}



void loop()
{   
  checkConnection();

    if(start){
      Receive();

      if(XofY){
          Wire.beginTransmission(0x08); //voor y naar beneden
          Wire.write(0x72);
          Wire.endTransmission();
         if(sensorY){
          Wire.beginTransmission(0x08);
          Wire.write(0x73);
          Wire.endTransmission();
          XofY = false;
//        start = false;
         }
      }else{
          Wire.beginTransmission(0x08);
          Wire.write(0x70);
          Wire.endTransmission();
        if(sensorX){
          Wire.beginTransmission(0x08);
          Wire.write(0x71);
          Wire.endTransmission();
//          bool startupcheck = automode.homing(incomingEncoderX, counter, startupX, startupY);

//          if(startupcheck = true){
            start = false;
//          }
//      }
      }

    }
    }
    else{
    geefCoords();
   
    state = button.getState();
    state2 = noodstop.getState();
    state3 = modus.getState();

    Receive();

    ButtonState currentState = Default;

    if (state2 == LOW && previousState2 == HIGH && noodstopPressed == false) {
        currentState = Noodstop;
    } else if (state2 == LOW && state3 == LOW && noodstopPressed == true) {
        currentState = NoodstopReleased;
    } else if (state == HIGH && previousState == LOW && noodstopPressed == false) {
        currentState = AanUit;
    } else if (state3 == LOW && previousState3 == HIGH && state2 == HIGH && noodstopPressed == false && werkenPressed == true) {
        currentState = Modus;
    } else {
        currentState = Default;
    }

    switch (currentState){
        case Noodstop:
            noodstopPressed = true;
            green = !green;
//            Serial.print(": Noodstop pressed");
            noodstopState = !noodstopState;
            Connection();
            setColor(255,0,0);
//            Serial.print(": ACTIVATED");
            Serial.write('c');
            Serial.write(3);
            
            break;
        case NoodstopReleased:
            noodstopPressed = false;
            modusState = false;
            green = false;
//            Serial.print(": Noodstop released");
            noodstopState = !noodstopState;
            Connection();
            setColor(235,129,0);
//            Serial.print(": RELEASED");
            Serial.write('c');
            Serial.write(2);
            break;
        case AanUit:
            werken = !werken;
            werkenPressed = !werkenPressed;
//            Serial.print(": AAN/UIT pressed ");
            if (werkenPressed == true)
            {
//                Serial.print(": SYSTEEM AAN");
            }else{
//                Serial.print(": SYSTEEM UIT");
            }
            Connection();
            if (green == true && werkenPressed == true) {
                setColor(0,255,0);
                Serial.write('c');
                Serial.write(1);
            } else if (green == false && werkenPressed == true) {
                setColor(235,129,0);
                Serial.write('c');
                Serial.write(2);
            }else if (werkenPressed == false) {
                setColor(0,0,0);
                Serial.write('c');
                Serial.write(4);
            }
            break;
        case Modus:
//            Serial.print(": Modus changed"); 
            modusState = !modusState;  
            if (green == false) {
                setColor(0,255,0);
                Serial.write('c');
                Serial.write(1);
            }else{
                setColor(235,129,0);
                Serial.write('c');
                Serial.write(2);
            }
            green = !green;
            Connection();
            break;
        case Default:
            break;

    }
          
    previousState = state;
    previousState2 = state2;
    previousState3 = state3;

   if(noodstopPressed == HIGH || werkenPressed == false){
//    Serial.println("Noodstop ingedrukt");
//    Wire.beginTransmission(0x08);
//    Wire.write(0xa1);
//    Wire.endTransmission();
    Wire.beginTransmission(0x08);
    Wire.write(0x11);
    Wire.endTransmission();
    motorA.stop();
    joystick.manualMove(HIGH);
   } else if((werkenPressed == true && noodstopPressed == false && modusState == true) || werken == true){
    joystick.manualMove(LOW);
   } else if ((modusState == false && noodstopPressed == false) || Auto == true){
    automode.autoMove(incomingEncoderX, counter, incomingX, incomingY);
   } else if (werkenPressed == false || modusState == true){
        motorA.stop();
    }
  
    }

}


void checkConnection() {
    unsigned long currentTime = millis();

    if (currentTime - lastPingTime >= PING_INTERVAL) {
        Serial.write('P');

        waitingForPong = true;
    }
    while (Serial.available() > 0) {

        if (Serial.read() == 0) {
                noodstopPressed = false;
       green = !green;
           noodstopState = !noodstopState;
           Connection();
           setColor(235,129,0);
        lastPingTime = currentTime;
            waitingForPong = false; 
            return;
        }
    }

    if (waitingForPong && currentTime - lastPingTime >= PING_TIMEOUT) {
        Serial.println("Noodstop"); 
              noodstopPressed = true;
       green = !green;
//            Serial.print(": Noodstop pressed");
           noodstopState = !noodstopState;
           Connection();
           setColor(255,0,0);
        waitingForPong = false; 
      
    }
}

void setColor(int redValue, int greenValue, int blueValue)
{
    digitalWrite(redPin, redValue);
    digitalWrite(greenPin, greenValue);
}

void Connection()
{
    
if (noodstopPressed == true) {
//    Serial.print(": Sending ACTIVATED");
    Wire.beginTransmission(0x08);
    Wire.write(0x02);
    Wire.endTransmission();
} else if (werkenPressed == false) {
//    Serial.print(": Sending UIT");
    Wire.beginTransmission(0x08);
    Wire.write(0x02);
    Wire.endTransmission();
} else if (modusState == true) {
//    Serial.print(": Sending AAN");
    Wire.beginTransmission(0x08);
    Wire.write(0xa1);
    Wire.endTransmission();
} else if (modusState == false) {
//    Serial.print(": Sending UIT");
    Wire.beginTransmission(0x08);
    Wire.write(0x02);
    Wire.endTransmission();
} else if (noodstopPressed == false && werkenPressed == true) {
//    Serial.print(": Sending RELEASED");
    Wire.beginTransmission(0x08);
    Wire.write(0xa1);
    Wire.endTransmission();
}
}

void Receive(){
    Wire.requestFrom(0x08, 3);
    while (Wire.available()) {
        
        int regId = Wire.read(); // byte 1
        int highByte = Wire.read(); // byte 2
        int lowByte = Wire.read(); // byte 3
        int data = (highByte << 8) | lowByte;
        
        switch (regId) {
            case 10:
                incomingEncoderX = data;
                
                sensorY = false;
                sensorX = true;
//                Serial.println(incomingEncoderX);
                break;
            case 20:
                int incomingMessage = data;
                if (incomingMessage == 0)
                { 
                    sensorY = true;
                    sensorX = false;
                }
                break;
            default:
                // Serial.println("Unknown regId: " + String(regId));
                sensorX = false;
                break;
        }
        berekenVerschil(incomingEncoderX, counter);
    }
}

void berekenVerschil(int nieuweX, int nieuweY){
  if(oudeX < nieuweX){
    beweegCounter += (nieuweX - oudeX);
  }
  else if(oudeX > nieuweX){
    beweegCounter += (oudeX - nieuweX);
  }
  checkBeweegCounter();
  
  if(oudeY < nieuweY){
    beweegCounter += (nieuweY - oudeY);
  }
  else if(oudeY > nieuweY){
    beweegCounter += (oudeY - nieuweY);
  }
  checkBeweegCounter();
}

void checkBeweegCounter(){
  int Xmap = map(incomingEncoderX, 0, 5850, 0, 255);
  int Ymap = map(counter, 0, 5000, 0, 255);
  if(beweegCounter >= 1000){
    beweegCounter = 0;
    if (incomingEncoderX < 5800) {
      Serial.write('a');
      Serial.write(Xmap);
      Serial.write(Ymap);
    }
//    Serial.println("X is: ");
//    Serial.println(Xmap);
//    Serial.println("X is: ");
//    Serial.println(incomingEncoderX);
  }
}

void geefCoords(){
  if(veranderCoords){
    if(Serial.available()> 0){
     if(Serial.read() == 9){
       noodstopPressed = true;
       green = !green;
//            Serial.print(": Noodstop pressed");
           noodstopState = !noodstopState;
           Connection();
           setColor(255,0,0);
//            Serial.print(": ACTIVATED");
           Serial.write('c');
           Serial.write(3);
     }
     else if(Serial.read() == 8){
       noodstopPressed = false;
           modusState = false;
           green = false;
           noodstopState = !noodstopState;
           Connection();
           setColor(235,129,0);
           Serial.write('c');
           Serial.write(2);
     }
     else if(changeX){
          incomingX = Serial.read();
          changeX = false;
          changeY = true;
      }
      else{
          if(changeY){
          incomingY = Serial.read();
          changeY = false;
          changeX = true;
          automode.changeConfirmTrue();
          automode.setfase();
//        veranderCoords = false;
        }
      }
//      }
    
      
   
//     incomingX = Serial.read();
//     incomingY = Serial.read();
//     Serial.println("X is: ");
//     Serial.println(incomingX);
//     incomingY = Serial.read();
    }
  }
}



void handleEncoder() {
  int clkState = digitalRead(CLK_PIN);
  int dtState = digitalRead(DT_PIN);

  if (clkState != lastClkState) {
    if (dtState != clkState) {
      counter++;
    } else {
      counter--;
    }
  }

if (sensorY == true)
  {
    counter = 0;
  }

lastClkState = clkState;
  
//Serial.println(counter);

}
