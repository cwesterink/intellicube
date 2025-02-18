#include "Debouncer.h"
#include <stdint.h>
#include <Arduino.h>
#include "Cube.h"

template <typename T> 

Debouncer<T>::Debouncer(const T initValue, const unsigned long debounceDelay) {
    _stableValue = initValue;
    _lastChangeTime = millis();
    _debounceDelay = debounceDelay;
}

template <typename T>

T Debouncer<T>::update(const T value) {
    unsigned long now = millis();

    if (value != _stableValue) {
        if (now - _lastChangeTime >= _debounceDelay) {
            _stableValue = value;
            _lastChangeTime = now;
        }
    } else {
        _lastChangeTime = now;
    }

    return _stableValue;
}

template class Debouncer<face_t>;
