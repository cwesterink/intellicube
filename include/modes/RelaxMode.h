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

        rgb_color getColor() override { return rgb_color(0, 128, 255); }
        String getName() override { return "Relax"; }

    private:
};

#endif