#include "RotaryEncoder.h"

RotaryEncoderResult RotaryEncoder::read() {
    int32_t rawPosition = _encoder.read();
    RotaryEncoderResult result;
    result.position = rawPosition / -4;
    result.changed = rawPosition != _prevPosition;

    _prevPosition = rawPosition;
    return result;
}

void RotaryEncoder::reset() {
    _prevPosition = 0;
    _encoder.write(0);
}

void RotaryEncoder::write(int32_t value) {
    _prevPosition = value * -4;
    _encoder.write(value * -4);
}