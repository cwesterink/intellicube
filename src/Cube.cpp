#include "Arduino.h"
#include "Cube.h"

Cube::Cube(const int sensorPins[4]): 
    _sensorPins{0},
    _pattern{false},
    _faceDebouncer(0, 3000)
{
    for (int i = 0; i < 4; i++) {
        pinMode(sensorPins[i], INPUT);
        _sensorPins[i] = sensorPins[i];
    }
}

face_t Cube::getTestFace(const bool pattern[4]) {
    for (size_t i = 0; i < 4; i++) {
        _pattern[i] = pattern[i];
    }
    
    return _getRawFace();
}

face_t Cube::getFace() {
  // Get the raw face from the sensor readings.
    _readSensors();
    face_t currentFace = _getRawFace();
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

void Cube::display() {
    Serial.print(_pattern[0]);
    Serial.print("  ");
    Serial.println(_pattern[1]);

    Serial.print(_pattern[3]);
    Serial.print("  ");
    Serial.println(_pattern[2]);
}

face_t Cube::_getRawFace() {

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
        return 0;
    case 1:
        return 1;
    case 2:
        if (noStreak) {
            return 3;
        } else {
            return 2;
        }
    case 3:
        return 4;
    case 4:
        return 5;

    default:
        return -1;
    }
}
