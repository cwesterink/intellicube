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
            : _state(SETUP), _startTime(0), _elapsedTime(0), _timerDuration(0) {};
        void update() override;    // Update the timer (elapsed time)
        void display() override;   // Display the timer on the LCD
        
        void onButtonEvent(ButtonEvent event) override;
        int32_t onEncoderChange(int32_t encoderVal) override;

    private:
        enum TimerState {
            SETUP,
            RUNNING,
        };
        TimerState _state;  // Timer state
        unsigned long _startTime;  // Start time in milliseconds
        unsigned long _elapsedTime;  // Elapsed time in seconds
        unsigned long _timerDuration;
        unsigned long encoderValueToDuration(long value);  // Convert encoder value to time in seconds
};

#endif