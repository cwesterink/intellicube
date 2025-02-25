#include "ColorModule.h"


PololuLedStrip<LED_PIN> ledStrip;

ColorModule::ColorModule() : _prevFace(255) {

    _modeColor[0] = {0, 255, 0};  
    _modeColor[1] = {255, 0, 0};  
    _modeColor[2] = {0, 0, 255};  
    _modeColor[3] = {255, 255, 0};
    _modeColor[4] = {0, 255, 255};
    _modeColor[5] = {255, 0, 255};
    _currentColor[0] = _modeColor[0];
}

void ColorModule::setColor(face_t face, rgb_color color) {
    _modeColor[face] = color;
}

void ColorModule::overrideColor(rgb_color color) {
    for (int i = 0; i < LED_COUNT; i++){
        _currentColor[i] = color;
    }
}

rgb_color ColorModule::getColor(face_t face) {
    return _modeColor[face];
}

void ColorModule::update(face_t face) {
    if (face != _prevFace) {
        _prevFace = face;
        for (int i = 0; i < LED_COUNT; i++){
            _currentColor[i] = _modeColor[face];
        }
    }
}

void ColorModule::display() {
    ledStrip.write(_currentColor, LED_COUNT);
}