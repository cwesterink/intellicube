#ifndef COLORMODULE_H
#define COLORMODULE_H

#include <Arduino.h>
#include <Wire.h>
#include <PololuLedStrip.h>

const int LED_COUNT = 42;

class ColorModule {
    public:
        ColorModule();
        // void overrideColor(rgb_color color); TODO: implement
        void display(rgb_color color);
        void turnOff();
        void turnOn();
        
    private:
        rgb_color _prevColor;
        rgb_color _colorArray[LED_COUNT];
        bool _lights_on = true;
};

#endif
