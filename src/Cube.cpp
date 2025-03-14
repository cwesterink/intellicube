#include "Arduino.h"
#include "Cube.h"

Cube::Cube():
    _pattern{false},
    _faceDebouncer(Face::HOME, 2000)
{
    for (int i = 0; i < 4; i++) {
        pinMode(SENSOR_PINS[i], INPUT);
        _sensorPins[i] = SENSOR_PINS[i];
    }
}

Face Cube::getFace() {
  // Get the raw face from the sensor readings.
    _readSensors();
    Face currentFace = _getRawFace();
    return _faceDebouncer.update(currentFace);
}

bool Cube::_readSensor(int sensor) {
    return digitalRead(_sensorPins[sensor]);
}

void Cube::_readSensors() {
    for (int i = 0; i < 4; i++) {
        _pattern[i] = _readSensor(i);
    }
}

Face Cube::_getRawFace() {

    int numOnes = 0;
    bool noStreak = true;
    bool prev = !_pattern[0];

    for (int i = 0; i < 4; i++) {
        numOnes += _pattern[i];
        if (prev == _pattern[i]) {
            noStreak = false;
        }
        prev = _pattern[i];
    }

    switch (numOnes)
    {
    case 0:
        return Face::SETTINGS;
    case 1:
        return Face::GAME;
    case 2:
        if (noStreak) {
            return Face::HABIT;
        } else {
            return Face::TIMER;
        }
    case 3:
        return Face::RELAX;
    default:
        return Face::HOME;
    }
}
