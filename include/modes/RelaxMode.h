#ifndef RELAXMODE_H
#define RELAXMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>
#include <PololuLedStrip.h>

class RelaxMode : public Mode {
    public:
    RelaxMode() {};

        void display() override;
        void update() override { display(); }

        int32_t onEncoderChange(int32_t encoderVal) override;
        uint16_t getRefreshRate() override { return _refreshRate; }
        rgb_color getColor() override { return rgb_color(0, 128, 255); }
        String getName() override { return "Relax"; }

    private:
        uint16_t _refreshRate = 250;
        int _dropPositions[20] = {-1};
};

#endif