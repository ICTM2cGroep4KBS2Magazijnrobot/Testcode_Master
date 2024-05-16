// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"

// Define the analog pin numbers for the joystick
Joystick joystick(A2, A3, 7, motorA);

MotorControl motorA(12, 3, 10, 6,2,7); //vervang 0 door de juiste pin

//define the button pin
Button button(A4);

// Define the state of the button
bool state = LOW;
bool previousState = LOW;

// Define the werken flipflop
bool werken = false;

// Define the I2C Serial bytes


// Setup function
void setup() {
    //initialize the I2C communication as master
    Wire.begin();
    // Initialize serial communication
    Serial.begin(115200);
}

void loop()
{   
    // Get the state of the button
    state = button.getState();
    // Check if the button is pressed
    if (state == HIGH && previousState == LOW) {
        // Print a message
        werken = !werken;
        Connection();
    }
    // Update the previous state
    previousState = state;

    // Set manual move on or off
    if (werken == false) {
        joystick.manualMove(LOW);
    }
    else {
        joystick.manualMove(HIGH);
    }
}

















































void Connection()
{
    // Send the data to the Slave
    if (werken == false)
    {
        Wire.beginTransmission(0x08);
        Wire.write(0xa1);
        Wire.endTransmission();
    }
    else if (werken == true)
    {
        Wire.beginTransmission(0x08);
        Wire.write(0x02);
        Wire.endTransmission();
    }
}

void JSCReceive(){
    //receive a signal from the Jserialcomm protocol from JAVA

    if (Serial.available() > 0) {    
        byte incomingByte = 0;
    incomingByte = Serial.read(); // read the incoming byte:
    if (incomingByte != -1) {
        if (incomingByte == 0xa1) {
            werken = true;
        }
        Connection();
    }
    }
}

    void JSCSend(){
    //send a signal from the Jserialcomm protocol from JAVA
    if (werken == false)
    {
        Serial.write("Handmatig");
    }
    else if (werken == true)
    {
        Serial.write("Automatish");




    }






}

