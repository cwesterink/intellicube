// HabitMode.h
#ifndef HABITMODE_H
#define HABITMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

struct habit_t {
    String name;
    bool completed;
};

class HabitMode : public Mode {
    public:
        HabitMode(LiquidCrystal_I2C &screen)
            : Mode(screen), _screen(screen) {}
        void update() override;    // Update the timer (elapsed time)
        void display() override;   // Display the timer on the LCD
        void onButtonClick() override;
        int onEncoderChange(int32_t encoderVal) override;

    private:
        LiquidCrystal_I2C &_screen;  // LCD screen
        habit_t _habits[4] = {
            {"Drink water", false},
            {"Exercise", false},
            {"Read", false},
            {"Meditate", false}
        };
        uint8_t _selectedHabitId = 0;
        const uint8_t _numHabits = 4;
};

#endif