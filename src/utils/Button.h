#include <stdint.h>
#ifndef BUTTON_H
#define BUTTON_H 

class Button {
    public:
        Button(int pin);
        bool isPressed();

    private:
        int _pin;
        bool prevValue;
        bool currValue;
};

#endif