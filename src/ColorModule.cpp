#include "ColorModule.h"
#include <Pins.h>


PololuLedStrip<LED_PIN> ledStrip;

bool colorsEqual(rgb_color color1, rgb_color color2) {
    return color1.red == color2.red && 
        color1.green == color2.green &&
        color1.blue == color2.blue;
}

ColorModule::ColorModule() : _prevColor({0, 0, 0}) {
    for (int i = 0; i < LED_COUNT; i++){
        _colorArray[i] = {0, 0, 0};
    }
}

void ColorModule::display(rgb_color color) {
    if (colorsEqual(color, _prevColor) || !_lights_on) {
        return;
    }
    _prevColor = color;
    for (int i = 0; i < LED_COUNT; i++){
        _colorArray[i] = color;
    }
    ledStrip.write(_colorArray, LED_COUNT);
}

void ColorModule::turnOff() {
    _lights_on = false;
    _prevColor = {0, 0, 0};
    for (int i = 0; i < LED_COUNT; i++){
        _colorArray[i] = {0, 0, 0};
    }
    ledStrip.write(_colorArray, LED_COUNT);
}

void ColorModule::turnOn() {
    _lights_on = true;
}