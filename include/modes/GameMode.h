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
        GameMode(): _waitTime(0), _elapsedTime(0), _startTime(0) {};
        void update() override;    // Update the timer (elapsed time)
        void display() override;   // Display the timer on the LCD

        rgb_color getColor() override { return rgb_color(0, 255, 128); }
        
        String getName() override { return "Game"; }
        
        void onButtonEvent(ButtonEvent event) override;

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