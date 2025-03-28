#include <Arduino.h>
#include "modes/SettingsMode.h"
#include <LiquidCrystal_I2C.h>
#include "ColorModule.h"
#include "RotaryEncoder.h"
extern LiquidCrystal_I2C lcd;
extern ColorModule colorModule;

void SettingsMode::display() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("------ Config ------");
    lcd.setCursor(0, 1);
    lcd.print("Lights: ");
    if (_lightOn) {
        lcd.print("On ");
    } else {
        lcd.print("Off");
    }
}

void SettingsMode::onButtonEvent(ButtonEvent event) {
    if (event == ButtonEvent::Click) {
        _lightOn = !_lightOn;
        if (_lightOn) {
            colorModule.turnOn();
        } else {
            colorModule.turnOff();
        }
        display();
    }
}
