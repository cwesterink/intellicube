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
            display();
        }
    }
}

void GameMode::display() {
    // Display the game on the LCD
    lcd.clear();
    lcd.print("--- Reaction Time --");
    if (_state == SETUP) {
        if (_score > 0) {
            lcd.setCursor(5, 2);
            lcd.print("Score: ");
            lcd.print(_score);
            lcd.print("ms");

            lcd.setCursor(0, 3);
            lcd.print("High Score: ");
            lcd.print(_highScore); 
            lcd.print("ms");

        } else {
            lcd.setCursor(0, 1);
            lcd.print("1. Wait for beep");
            lcd.setCursor(0, 2);
            lcd.print("2. Click!");
            lcd.setCursor(0, 3);
            lcd.print("Press to start");
        }
    } else if (_state == WAIT) {
        lcd.setCursor(4, 2);
        lcd.print("Wait for beep");
    } else if (_state == LIVE) {
        lcd.setCursor(6, 2);
        lcd.print("CLICK!");
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
            if (_score < _highScore) {
                _highScore = _score;
            }
            _state = SETUP;
        }
        display();
    }
}
