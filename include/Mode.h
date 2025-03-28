// Mode.h
#ifndef MODE_H
#define MODE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Button.h"
#include <PololuLedStrip.h>

class Mode {
    public:
        Mode() {}
        virtual void update() {};
        virtual void display() = 0;
        virtual String getName() = 0;
        virtual rgb_color getColor() = 0;
        virtual uint16_t getRefreshRate() = 0;

        virtual void onButtonEvent(ButtonEvent event) {};
        virtual int32_t onEncoderChange(int32_t encoderVal) { return encoderVal; };
};

#endif
