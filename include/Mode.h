// Mode.h
#ifndef MODE_H
#define MODE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include "Button.h"

class Mode {
    public:
        Mode() {}
        virtual void update() {};   // Update the mode logic
        virtual void display() = 0;   // Display mode-specific info
        virtual void onButtonClick() {};
        virtual int onEncoderChange(int32_t encoderVal) { return 0; };
};

#endif
