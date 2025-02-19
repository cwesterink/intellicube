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
        virtual void update() {};
        virtual void display() = 0;

        virtual void onButtonEvent(ButtonEvent event) {};
        virtual int32_t onEncoderChange(int32_t encoderVal) { return encoderVal; };
};

#endif
