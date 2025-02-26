#include <stdint.h>
#include "Debouncer.h"
#include "Pins.h"

#ifndef CUBE_H   // if not defined CUBE_H
#define CUBE_H   // define CUBE_H

typedef uint8_t face_t;

int const SENSOR_PINS[4] = {TOP_LEFT_SENSOR_PIN, TOP_RIGHT_SENSOR_PIN, BOTTOM_RIGHT_SENSOR_PIN, BOTTOM_LEFT_SENSOR_PIN};

class Cube {
    public:
        Cube();
        face_t getFace();
        face_t getTestFace(const bool pattern[4]);
        void display();
    private:
        int _sensorPins[4];
        bool _pattern[4];
        Debouncer<face_t> _faceDebouncer;
        bool _readSensor(int sensor);
        void _readSensors();
        face_t _getRawFace();
};

#endif // CUBE_H