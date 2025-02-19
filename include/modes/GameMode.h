// GameMode.h
#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

extern LiquidCrystal_I2C lcd;

class GameMode : public Mode {
    public:
        GameMode() {};
        void update() override;    // Update the timer (elapsed time)
        void display() override;   // Display the timer on the LCD

        void onButtonEvent(ButtonEvent event) override;
        int32_t onEncoderChange(int32_t encoderVal) override;

    private:
        enum State {
            SETUP,
            WAIT,
            LIVE
        };

        State _state = SETUP;

        unsigned long _waitTime;
        unsigned long _elapsedTime;
        unsigned long _score = 0;
        unsigned long _startTime;  // Start time in milliseconds

};

#endif