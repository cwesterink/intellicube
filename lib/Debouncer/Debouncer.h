#include <stdint.h>
#ifndef DEBOUNCER_H
#define DEBOUNCER_H

template <typename T> 

class Debouncer {
    public:
        Debouncer(const T initValue, const unsigned long debounceDelay)
            : _stableValue(initValue), _debounceDelay(debounceDelay) {
                _lastChangeTime = millis();
            }
        T update(const T value) {
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
  
    private:
        T _stableValue;
        unsigned long _lastChangeTime; // Timestamp when a potential change was detected.
        unsigned long _debounceDelay; // Debounce delay
};

#endif