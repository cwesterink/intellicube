#include "ColorModule.h"


PololuLedStrip<LED_PIN> ledStrip;

ColorModule::ColorModule() : _prevFace(255) {

    _modeColor[0] = {255, 0, 0};  
    _modeColor[1] = {0, 255, 0};  
    _modeColor[2] = {0, 0, 255};  
    _modeColor[3] = {255, 255, 0};
    _modeColor[4] = {0, 255, 255};
    _modeColor[5] = {255, 0, 255};
    _currentColor[0] = _modeColor[0];
}

void ColorModule::setColor(face_t face, rgb_color color) {
    _modeColor[face] = color;
}

void ColorModule::update(face_t face) {
    if (face != _prevFace) {
        _prevFace = face;
        _currentColor[0] = _modeColor[face];
    }
}

void ColorModule::display() {
    ledStrip.write(_currentColor, LED_COUNT);
}