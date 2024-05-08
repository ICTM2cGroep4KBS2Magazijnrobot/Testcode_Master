// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"
//#include "Pruduct.h"


// Define the analog pin numbers for the joystick
Joystick joystick(A2, A3, 7);

//define the button pin
Button button(A4);

// int Cords[6] = {1,1,2,2,9,9};
// Pruduct doos[3] = {Pruduct(Cords[0], Cords[1]), Pruduct(Cords[2], Cords[3]), Pruduct(Cords[4], Cords[5])};

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
    // Serial.print(button.getState());
    // Serial.print(" : ");
    state = button.getState();
    // Check if the button is pressed
    if (state == HIGH && previousState == LOW) {
        // Print a message
        Serial.print(": Button pressed ");
        werken = !werken;
        Connection();
    }
    // Update the previous state
    previousState = state;
    //Serial.println(werken);

   
    // doos[0].read();
    // doos[1].read();
    // doos[2].read();
   
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
        Serial.print(": Sending 1");
        Wire.beginTransmission(0x08);
        Wire.write(0xa1);
        Wire.endTransmission();
    }
    else if (werken == true)
    {
        Serial.print(": Sending 2");
        Wire.beginTransmission(0x08);
        Wire.write(0x02);
        Wire.endTransmission();
    }
}

