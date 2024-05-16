// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"
//#include "Pruduct.h"

// Define the pins for the RGB LED
int redPin = 4;
int greenPin = 5;

int lastClkState = HIGH;
int counter = 0;


const int CLK_PIN = 2;
const int DT_PIN = 7;

// Define the analog pin numbers for the joystick
Joystick joystick(A2, A3, 7, motorA);

MotorControl motorA(12, 3, 10, 6,2,7); //vervang 0 door de juiste pin

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
bool noodstopState = false;
bool modusState = false;

bool werkenPressed = false;
bool noodstopPressed = false;
bool green = false;

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

    // motorA.read();
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
        // setColor(0,0,0);
        // werkenPressed = !werkenPressed;
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
        // noodstopPressed = true;
        if (noodstopPressed == true)
        {
            Serial.print(": ACTIVATED");
        }
    }

    if (state2 == LOW && state3 == LOW  && noodstopPressed == true) {
        // Print a message
        noodstopPressed = false;
        Serial.print(": Noodstop released");
        noodstopState = !noodstopState;
        Connection();
        setColor(235,129,0);
        // noodstopPressed = false;
        if (noodstopPressed == false)
        {
            Serial.print(": RELEASED");
        }
        
    }

    if (state3 == LOW && previousState3 == HIGH && state2 == HIGH && noodstopPressed == false && werkenPressed == true) {
        Serial.print(": Modus changed");        
        if (green == false) {
            modusState = !modusState;
            setColor(0,255,0);
        }if (green == true) {
            modusState = !modusState;
            setColor(235,129,0);
        }
        if (green == false) {
            green = true;
        }else{
            green = false;
        }
    }           
    
    // Update the previous state
    previousState = state;
    previousState2 = state2;
    previousState3 = state3;
    //Serial.println(werken);
   
    // Set manual move on or off
    if (werkenPressed == true || noodstopPressed == false) { // LOW is dat ie wel mag bewegen
        joystick.manualMove(LOW);
    }
    if (werkenPressed == false)
    {
        // joystick.manualMove(HIGH);
        motorA.stop();
    }
    if (noodstopPressed == HIGH)
    {
        // joystick.manualMove(HIGH);
        motorA.stop();
    }    
}

















































void Connection()
{
    // Send the data to the Slave
    if (werkenPressed == true && noodstopPressed == false)
    {
        Serial.print(": Sending AAN");
        Wire.beginTransmission(0x08);
        Wire.write(0xa1);
        Wire.endTransmission();
    }
    if (werkenPressed == false)
    {
        Serial.print(": Sending UIT");
        Wire.beginTransmission(0x08);
        Wire.write(0x02);
        Wire.endTransmission();
    }
    if (noodstopPressed == true)
    {
        Serial.print(": Sending ACTIVATED");
        Wire.beginTransmission(0x08);
        Wire.write(0x02);
        Wire.endTransmission();
    }
    if (noodstopPressed == false && werkenPressed == true)
    {
        Serial.print(": Sending RELEASED");
        Wire.beginTransmission(0x08);
        Wire.write(0xa1);
        Wire.endTransmission();
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

