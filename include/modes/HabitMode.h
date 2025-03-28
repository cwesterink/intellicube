// HabitMode.h
#ifndef HABITMODE_H
#define HABITMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

struct habit_t {
    String name;
    bool completed;
};

class HabitMode : public Mode {
    public:
        HabitMode() {};
        void update() {};
        void display() override;

        rgb_color getColor() override { return rgb_color(128, 0, 255); }
        String getName() override { return "Habit"; }
        uint16_t getRefreshRate() override { return 0; }

        void onButtonEvent(ButtonEvent event) override;
        int32_t onEncoderChange(int32_t encoderVal) override;

    private:
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