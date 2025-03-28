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
        void update() override { display(); }
        void onButtonEvent(ButtonEvent event) override;
        uint16_t getRefreshRate() override { return 0; }

        rgb_color getColor() override { return rgb_color(255, 255, 128); }
        String getName() override { return "Settings"; }

    private:
        bool _lightOn = true;
};

#endif