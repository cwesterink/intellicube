#include <Arduino.h>
#include "modes/SettingsMode.h"
#include <LiquidCrystal_I2C.h>
#include "ColorModule.h"
#include "RotaryEncoder.h"
extern LiquidCrystal_I2C lcd;
extern ColorModule colorModule;
extern RotaryEncoder encoder;

void SettingsMode::displaySelection() {
    String listedModes[3];
    int firstIdx;
    if (_edditingFace < 3) {
        firstIdx = 0;
    } else {
        firstIdx = _edditingFace - 2;
    }

    for (int i = 0; i < 3; i++) {
        listedModes[i] = _modeNames[firstIdx + i];
    }

    lcd.clear();

    lcd.print("-------Config-------");

    for (int i = 0; i < 3; i++) {
        lcd.setCursor(0, i + 1);
        lcd.print(i+firstIdx == _edditingFace ? ">" : " ");
        
        lcd.print(listedModes[i]);
    }
    lcd.display();
}

void SettingsMode::displayEdit() {
    lcd.clear();
    lcd.print(_modeNames[_edditingFace]);
    lcd.setCursor(3, 2);
    lcd.print("RED|GREEN|BLUE");
    lcd.setCursor(3, 3);
    lcd.print(_currentColor.red);
    lcd.cursor_on();
    lcd.setCursor(6, 3);
    lcd.print("| ");
    lcd.print(_currentColor.green);
    lcd.setCursor(12, 3);
    lcd.print("|");
    lcd.print(_currentColor.blue);
    lcd.display();
}
void SettingsMode::display() {
    if (_state == SELECT) {
        displaySelection();
    } else {
        displayEdit();
    }
}

void SettingsMode::onButtonEvent(ButtonEvent event) {
    if (_state == SELECT) {
        if (event == ButtonEvent::Click) {
            _state = EDIT;
            encoder.write(_currentColor.red / COLOR_STEP);
        }
    } else {
        bool exit = false;
        if (event == ButtonEvent::Hold) {
            exit = true;
        } else if (event == ButtonEvent::Click) {
            switch (_editingState)
            {
            case RED:
                _editingState = GREEN;
                encoder.write(_currentColor.green / COLOR_STEP);
                break;
            case GREEN:
                _editingState = BLUE;
                encoder.write(_currentColor.blue / COLOR_STEP);
                break;
            default:
                colorModule.setColor((face_t)_edditingFace, _currentColor);
                exit = true;
                break;
            }
        }
        if (exit) {
            _state = SELECT;
            encoder.reset();
            _editingState = RED;
            _edditingFace = 0;
            _currentColor = colorModule.getColor(0);
            colorModule.overrideColor(_currentColor);
        }
    }
}

int32_t SettingsMode::onEncoderChange(int32_t encoderVal) {

    if (_state == SELECT) {
        _edditingFace = constrain(encoderVal, 0, 5);

        _currentColor = colorModule.getColor(_edditingFace);
        colorModule.overrideColor(_currentColor);
        return _edditingFace;
    } else {
        encoderVal = constrain(encoderVal, 0, 255 / COLOR_STEP);
    
        unsigned char newVal = encoderVal * COLOR_STEP;
        switch (_editingState)
            {
            case RED:
                _currentColor.red = newVal;
                break;
            case GREEN:
                _currentColor.green = newVal;
                break;
            default: // BLUE
                _currentColor.blue = newVal;
                break;
            }
        
        colorModule.overrideColor(_currentColor);
        return encoderVal;
    }
}
