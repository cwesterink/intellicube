// TimerMode.h
#ifndef TIMERMODE_H
#define TIMERMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

class TimerMode : public Mode {
    public:
        TimerMode()
            : _timerDuration(0) {};
        void display() override;   // Display the timer on the LCD
        
        void onButtonEvent(ButtonEvent event) override;
        int32_t onEncoderChange(int32_t encoderVal) override;

        uint16_t getRefreshRate() override { return 1000; }
        rgb_color getColor() override { return rgb_color(255, 0, 128); }
        String getName() override { return "Timer"; }

    private:
        unsigned long _timerDuration;
        unsigned long encoderValueToSeconds(long value);  // Convert encoder value to time in seconds
};

#endif