
//Button header file
//See gitHub for changes
// Created by: roboticsbackend.com


#ifndef Button_h
#define Button_h
#include <Arduino.h>

class Button {
  private:
    int _pin;
    int buttonPushCounter = 0;
    bool state;
    bool lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 0;
  public:
    Button(int pin);
    void init();
    void update();
    bool getState();
    bool isPressed();
    bool singleClick();
};

    Button::Button(int pin) {
      _pin = pin;
      lastReading = HIGH;
      init();
    }

    void Button::init() {
      pinMode(_pin, INPUT_PULLUP);

      update();
    }

    void Button::update() {
      // You can handle the debounce of the button directly
      // in the class, so you don't have to think about it
      // elsewhere in your code
      int newReading = digitalRead(_pin);
      
      if (newReading != lastReading) {
        lastDebounceTime = millis();
      }

      if (millis() - lastDebounceTime > debounceDelay) {
        // Update the 'state' attribute only if debounce is checked
        state = newReading;
      }
      lastReading = newReading;
    }

    bool Button::getState() {
      update();
      return state;
    }

    bool Button::isPressed() {
      return (getState() == HIGH);
    }


#endif