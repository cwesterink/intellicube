#ifndef SETTINGSMODE_H
#define SETTINGSMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>
#include <PololuLedStrip.h>

#define COLOR_STEP 15

class SettingsMode : public Mode {
    public:
        SettingsMode() {};

        void display() override;
        void onButtonEvent(ButtonEvent event) override;
        int32_t onEncoderChange(int32_t encoderVal) override;

    private:
        void displaySelection();
        void displayEdit();
        enum EditingState {
            RED,
            GREEN,
            BLUE
        };

        enum State {
            SELECT,
            EDIT,
        };

        String _modeNames[6] = {
            "Idle",
            "Timer",
            "Habit",
            "Pomodoro",
            "Game",
            "Settings"
        };
        State _state = SELECT;
        EditingState _editingState = RED;
        int _edditingFace = 0;
        rgb_color _currentColor;
};

#endif