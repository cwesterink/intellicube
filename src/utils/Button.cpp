#include "Arduino.h"
#include "Button.h"

Button::Button(int pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
    prevValue = 0;
    currValue = 0;
}

bool Button::isPressed() {
    prevValue = currValue;
    currValue = !digitalRead(_pin);
    return currValue && !prevValue;
}
