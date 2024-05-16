// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"
#include "MotorControl.h"
#include "AutoMode.h"
//#include "Pruduct.h"

// Define the pins for the RGB LED
int redPin = 4;
int greenPin = 5;

int lastClkState = HIGH;
int counter = 0;


const int CLK_PIN = 2;
const int DT_PIN = 7;

// Define the analog pin numbers for the MotorControl
MotorControl motorA(12, 3, 6,2,7); //vervang 0 door de juiste pin

// Define the analog pin numbers for the Joystick
Joystick joystick(A2, A3, 0, motorA);
// Define the analog pin numbers for the AutoMode
AutoMode automode(motorA);

//define the button pin
Button button(A4);
Button noodstop(8);
Button modus(9);

// Define the state of the button
bool state = LOW;
bool state2 = LOW;
bool state3 = LOW;
bool previousState = LOW;
bool previousState2 = LOW;
bool previousState3 = LOW;

// Define the flipflop
bool werken = true;
bool Auto = false;
bool noodstopState = false;
bool modusState = false;

bool werkenPressed = false;
bool noodstopPressed = false;
bool green = false;


String incomingString = "";
byte incomingByte = 0;
int incomingEncoderX = 0;

// Define the I2C Serial bytes

// Setup function
void setup() {
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), handleEncoder, CHANGE);

    //initialize the I2C communication as master
    Wire.begin();
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize the RGB Pins
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
}

// Function to set the color of the RGB LED
void setColor(int redValue, int greenValue, int blueValue)
{
    digitalWrite(redPin, redValue);
    digitalWrite(greenPin, greenValue);
}

void loop()
{   
    // Get the state of the button
    state = button.getState();
    state2 = noodstop.getState();
    state3 = modus.getState();
    // Check if the button is pressed
    if (state == HIGH && previousState == LOW && noodstopPressed == false) {
        // Print a message
        Serial.print(": AAN/UIT pressed ");
        werken = !werken;
        werkenPressed = !werkenPressed;
        Connection();
        if (green == true && werkenPressed == true) {
            setColor(0,255,0);
        }if (green == false && werkenPressed == true) {
            setColor(235,129,0);
        }if (werkenPressed == false) {
            setColor(0,0,0);
        }
        if (werkenPressed == true)
        {
            Serial.print(": SYSTEEM AAN");
        }else{
            Serial.print(": SYSTEEM UIT");
        }
    }

    if (state2 == LOW && previousState2 == HIGH && noodstopPressed == false) {
        // Print a message
        noodstopPressed = true;
        Serial.print(": Noodstop pressed");
        noodstopState = !noodstopState;
        Connection();
        setColor(255,0,0);
        Serial.print(": ACTIVATED");
    }

    if (state2 == LOW && state3 == LOW  && noodstopPressed == true) {
        // Print a message
        noodstopPressed = false;
        Serial.print(": Noodstop released");
        noodstopState = !noodstopState;
        Connection();
        setColor(235,129,0);
            Serial.print(": RELEASED");
    }

    if (state3 == LOW && previousState3 == HIGH && state2 == HIGH && noodstopPressed == false && werkenPressed == true) {
        Serial.print(": Modus changed"); 
        modusState = !modusState;  
        if (green == false) {
            setColor(0,255,0);
        }else{
            setColor(235,129,0);
        }
        green = !green;
        Connection();
    }           
    
    // Update the previous state
    previousState = state;
    previousState2 = state2;
    previousState3 = state3;

    // Set manual move on or off
   if(noodstopPressed == HIGH){
     motorA.stop();
   } else if((werkenPressed == true && noodstopPressed == false && modusState == true) || werken == true){
    joystick.manualMove(LOW);
    Serial.println("Handmatig");
   } else if ((modusState == false && noodstopPressed == false) || Auto == true){
    automode.autoMove(incomingEncoderX, counter);
    Serial.println("Auto");
   } else if (werkenPressed == false || modusState == true){
        motorA.stop();
    }
}
void Connection()
{
    // Send the data to the Slave
if (noodstopPressed == true) {
    Serial.print(": Sending ACTIVATED");
    Wire.beginTransmission(0x08);
    Wire.write(0x02);
    Wire.endTransmission();
} else if (werkenPressed == false) {
    Serial.print(": Sending UIT");
    Wire.beginTransmission(0x08);
    Wire.write(0x02);
    Wire.endTransmission();
} else if (modusState == true) {
    Serial.print(": Sending AAN");
    Wire.beginTransmission(0x08);
    Wire.write(0xa1);
    Wire.endTransmission();
} else if (modusState == false) {
    Serial.print(": Sending UIT");
    Wire.beginTransmission(0x08);
    Wire.write(0x02);
    Wire.endTransmission();
} else if (noodstopPressed == false && werkenPressed == true) {
    Serial.print(": Sending RELEASED");
    Wire.beginTransmission(0x08);
    Wire.write(0xa1);
    Wire.endTransmission();
}
}

void Receive(){
    Wire.requestFrom(0x08, 1);
    if (Wire.available() > 0) {
        incomingByte = Wire.read();
        incomingEncoderX = incomingByte;
    } 
}

void JSCReceive(){
    //receive a signal from the Jserialcomm protocol from JAVA

    if (Serial.available() > 0) {    
        char c = 0;
    c = Serial.read(); // read the incoming byte:
    if (c != -1) {
        incomingString += c;
        if (incomingString == "Handmatig") {
            werken = true;
            Auto = false;
        } else if(incomingString == "Automatish") {
            werken = false;
            Auto = true;
        }
        incomingString = ""; // clear the string:
        Connection();
    }
    }
}

    void JSCSend(){
    //send a signal from the Jserialcomm protocol from JAVA
    if (werken == true)
    {
        Serial.write("Handmatig");
    }
    else if (Auto == true)
    {
        Serial.write("Automatish");
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
  lastClkState = clkState;
  Serial.println(counter);

}

//     if (werkenPressed == true && noodstopPressed == false && modusState == true)
//     {
//         Serial.print(": Sending AAN");
//         Wire.beginTransmission(0x08);
//         Wire.write(0xa1);
//         Wire.endTransmission();
//     } if (modusState == false && noodstopPressed == false )
//     {
//         Serial.print(": Sending UIT");
//         Wire.beginTransmission(0x08);
//         Wire.write(0x02);
//         Wire.endTransmission();
//     } if (werkenPressed == false)
//     {
//         Serial.print(": Sending UIT");
//         Wire.beginTransmission(0x08);
//         Wire.write(0x02);
//         Wire.endTransmission();
//     }  if (noodstopPressed == true)
//     {
//         Serial.print(": Sending ACTIVATED");
//         Wire.beginTransmission(0x08);
//         Wire.write(0x02);
//         Wire.endTransmission();
//     } if (noodstopPressed == false && werkenPressed == true)
//     {
//         Serial.print(": Sending RELEASED");
//         Wire.beginTransmission(0x08);
//         Wire.write(0xa1);
//         Wire.endTransmission();
//     }
