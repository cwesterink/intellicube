#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

enum class ButtonEvent { None, Click, DoubleClick, Hold, Release };

class Button {
public:
    Button(uint8_t pin);
    
    void update();             // Call this frequently to track button state
    ButtonEvent getEvent();    // Get the last button event (clears after read)

private:
    uint8_t _pin;
    bool _lastState;
    unsigned long _lastPressTime;
    unsigned long _lastReleaseTime;
    ButtonEvent _lastEvent;
};

#endif
