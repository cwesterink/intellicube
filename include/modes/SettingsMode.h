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

        rgb_color getColor() override { return rgb_color(255, 255, 128); }
        String getName() override { return "Settings"; }

    private:
        bool _lightOn = true;
};

#endif