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
byte werkenByte = 0;


// Setup function
void setup() {
    //initialize the I2C communication as master
    Wire.begin(0xAA);


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
        Serial.println("Button pressed");
        werken = !werken;

    }
    // Update the previous state
    previousState = state;
    Timer(millis(), 100);

    // Send the data to the Slave
    Connectie();

    // Set manual move on or off
    if (werken == false) {
        joystick.manualMove(LOW);
    }
    else {
        joystick.manualMove(HIGH);
    }
}


void Connectie()
{
    werkenByte = werken; //convert the boolean to a byte
    Wire.beginTransmission(0x08);// informs the bus that we will be sending data to slave
    Wire.write(werkenByte); // sends the data to the slave
    Wire.endTransmission(); //informs the bus that we will stop sending data to the slave
}