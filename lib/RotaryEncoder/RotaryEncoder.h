#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <Arduino.h>
#include <Encoder.h>

struct RotaryEncoderResult {
    int32_t position;
    bool changed;
};

class RotaryEncoder {
    public:
        RotaryEncoder(int pin1, int pin2) 
            : _encoder(pin1, pin2), _prevPosition(0)  {};
            
        RotaryEncoderResult read();
        void reset();
        void write(int32_t value);

    private:
        Encoder _encoder;
        int32_t _prevPosition;
};

#endif