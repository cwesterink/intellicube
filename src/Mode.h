// Mode.h
#ifndef MODE_H
#define MODE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include "utils/Button.h"

class Mode {
    public:
        Mode(LiquidCrystal_I2C &screen)
            : _screen(screen) {}
        virtual void update() {};   // Update the mode logic
        virtual void display() = 0;   // Display mode-specific info
        virtual void onButtonClick() {};
        virtual int onEncoderChange(int32_t encoderVal) { return false; };

        // You can also add state variables here that are common across all modes
    protected:
        LiquidCrystal_I2C &_screen;  // LCD screen
};

#endif
