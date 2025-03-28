#include <Arduino.h>
#include "modes/MuliMode.h"
#include <LiquidCrystal_I2C.h>
#include <algorithm>

extern LiquidCrystal_I2C lcd;

void MultiMode::display() {
    if (!isSelected) {

        int firstIdx;
        if (_selectedMode < 3) {
            firstIdx = 0;
        } else {
            firstIdx = _selectedMode - 2;
        }
    
        lcd.clear();

        lcd.print("-------");
        lcd.print(_name);
        lcd.print("-------");
    
        size_t numRows = std::min((size_t)3, _modeCount);
        for (size_t i = 0; i < numRows; i++) {
            lcd.setCursor(0, i + 1);
            lcd.print(i+firstIdx == _selectedMode ? ">" : " ");
            lcd.print(_modes[i+firstIdx]->getName());
        }
        lcd.display();
        return;
    }
    _modes[_selectedMode]->display();
}

void MultiMode::onButtonEvent(ButtonEvent event) {
    if (!isSelected) {
        if (event == ButtonEvent::Click) {
            isSelected = true;
            display();
        }
    } else if (event == ButtonEvent::Hold) {
        isSelected = false;
        display();
    } else {
        _modes[_selectedMode]->onButtonEvent(event);
    }
};


int32_t MultiMode::onEncoderChange(int32_t encoderVal) {
    if (!isSelected) {
        _selectedMode = constrain(encoderVal, 0, _modeCount - 1);
        if (_selectedMode == encoderVal) {
            // Within bounds, refresh screen
            display();
        }
        return _selectedMode;
    }
    return _modes[_selectedMode]->onEncoderChange(encoderVal);
};