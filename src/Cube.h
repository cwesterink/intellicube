#include <stdint.h>
#include "utils/Debouncer.h"
#ifndef CUBE_H   // if not defined CUBE_H
#define CUBE_H   // define CUBE_H

typedef uint8_t face_t;

class Cube {
    public:
        Cube(const int sensorPins[4]);
        face_t getFace();
        face_t getTestFace(const bool pattern[4]);
        void display();
    private:
        Debouncer<face_t> _faceDebouncer;
        int _sensorPins[4];
        bool _pattern[4];
        bool _readSensor(int sensor);
        void _readSensors();
        face_t _getRawFace();
};

#endif // CUBE_H