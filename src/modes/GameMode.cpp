#include "modes/GameMode.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Pins.h"

void GameMode::update() {
    // Update the game logic
    if (_state == WAIT) {
        if (millis() - _startTime >= _waitTime) {
            _state = LIVE;
            _startTime = millis();
            tone(BUZZER_PIN, 1000, 250);
        }
    }
}

void GameMode::display() {
    // Display the game on the LCD
    lcd.clear();
    lcd.print("Game Mode");
    if (_state == SETUP) {
        lcd.setCursor(0, 1);
        lcd.print("Press to start");
        if (_score > 0) {
            lcd.setCursor(0, 2);
            lcd.print("Last score: ");
            lcd.print(_score);
        }
    } else if (_state == WAIT) {
        lcd.setCursor(0, 1);
        lcd.print("Wait...");
    } else if (_state == LIVE) {
        lcd.setCursor(0, 1);
        lcd.print("Press to stop");
    }
}

void GameMode::onButtonEvent(ButtonEvent event) {
    if (event == ButtonEvent::Click) {
        if (_state == SETUP) {
            _waitTime = random(1000, 5000);
            _state = WAIT;
            _startTime = millis();
        } else if (_state == LIVE) {
            _score = millis() - _startTime;
            _state = SETUP;
        }
    }

}

int32_t GameMode::onEncoderChange(int32_t encoderVal) {
    // Handle encoder changes
    return encoderVal;
}
