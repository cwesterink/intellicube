#include <stdint.h>
#include "Debouncer.h"
#include "Pins.h"

#ifndef CUBE_H   // if not defined CUBE_H
#define CUBE_H   // define CUBE_H

int const SENSOR_PINS[4] = {TOP_LEFT_SENSOR_PIN, TOP_RIGHT_SENSOR_PIN, BOTTOM_RIGHT_SENSOR_PIN, BOTTOM_LEFT_SENSOR_PIN};

enum class Face {
    HOME,
    TIMER,
    HABIT,
    GAME,
    RELAX,
    SETTINGS
};

class Cube {
    public:
        Cube();
        Face getFace();
        Face getTestFace(const bool pattern[4]);
        void display();
    private:
        int _sensorPins[4];
        bool _pattern[4];
        Debouncer<Face> _faceDebouncer;
        bool _readSensor(int sensor);
        void _readSensors();
        Face _getRawFace();
};

#endif // CUBE_H