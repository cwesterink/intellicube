#ifndef COLORMODULE_H
#define COLORMODULE_H

#include <Arduino.h>
#include <Wire.h>
#include <PololuLedStrip.h>
#include "Cube.h"

const int LED_COUNT = 1;

class ColorModule {
    public:
        ColorModule();
        void setColor(face_t face, rgb_color color);
        void update(face_t face);
        void display();

    private:
        rgb_color _modeColor[6];
        rgb_color _currentColor[LED_COUNT];
        face_t _prevFace;
};

#endif
