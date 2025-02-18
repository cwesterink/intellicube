#include <stdint.h>
#ifndef DEBOUNCER_H
#define DEBOUNCER_H

template <typename T> 

class Debouncer {
    public:
        Debouncer(const T initValue, const unsigned long debounceDelay);
        T update(const T value);
  
    private:
        T _stableValue;
        unsigned long _lastChangeTime; // Timestamp when a potential change was detected.
        unsigned long _debounceDelay; // Debounce delay
};

#endif