// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"


// Define the analog pin numbers for the joystick
Joystick joystick(A2, A3, 7);

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
    Serial.print(button.getState());
    Serial.print(" : ");
    state = button.getState();
    // Check if the button is pressed
    if (state == HIGH && previousState == LOW) {
        // Print a message
        Serial.println("Button pressed");
        werken = !werken;
        Connection();

    }
    // Update the previous state
    previousState = state;

    // Send the data to the Slave

    
    Serial.print("Werken: ");
    Serial.println(werken);


    // Set manual move on or off
    if (werken == false) {
        joystick.manualMove(LOW);
        //motorA.Sensorread();
    }
    else {
        joystick.manualMove(HIGH);
        //motorA.Sensorread();
        ;
    }
}

void Connection()
{
    // Send the data to the Slave
    Wire.beginTransmission(0x08);
    Wire.write(werken);
    Wire.endTransmission();
}

