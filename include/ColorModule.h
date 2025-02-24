#ifndef COLORMODULE_H
#define COLORMODULE_H

#include <Arduino.h>
#include <Wire.h>
#include <PololuLedStrip.h>
#include "Cube.h"

const int LED_COUNT = 42;

class ColorModule {
    public:
        ColorModule();
        void overrideColor(rgb_color color);
        void setColor(face_t face, rgb_color color);
        rgb_color getColor(face_t face);
        void update(face_t face);
        void display();

    private:
        rgb_color _modeColor[6];
        rgb_color _currentColor[LED_COUNT];
        face_t _prevFace;
};

#endif
