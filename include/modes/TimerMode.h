// TimerMode.h
#ifndef TIMERMODE_H
#define TIMERMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

extern LiquidCrystal_I2C lcd;

class TimerMode : public Mode {
    public:
        TimerMode()
            : _timerDuration(0) {};
        void display() override;   // Display the timer on the LCD
        
        void onButtonEvent(ButtonEvent event) override;
        int32_t onEncoderChange(int32_t encoderVal) override;

        String getName() override { return "Timer"; }

    private:
        unsigned long _timerDuration;
        unsigned long encoderValueToSeconds(long value);  // Convert encoder value to time in seconds
};

#endif