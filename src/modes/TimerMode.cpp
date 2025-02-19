#include "modes/TimerMode.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Pins.h"

int32_t TimerMode::onEncoderChange(int32_t encoderVal) {
    if (_state == SETUP) {
        _timerDuration = encoderValueToDuration(encoderVal);
        if (encoderVal < 0) {
            return 0;
        }
    }
    return encoderVal;
}


void TimerMode::update() {
    if (_state == RUNNING) {
        _elapsedTime = (millis() - _startTime);
        if (_elapsedTime >= _timerDuration) {
            _state = SETUP;
            tone(BUZZER_PIN, 1000, 2000);
        }
    }
}

void TimerMode::onButtonEvent(ButtonEvent event) {
    if (event == ButtonEvent::Click) {
        if (_state == SETUP) {
            _state = RUNNING;
            _startTime = millis();
        } else if (_state == RUNNING) {
            _state = SETUP;
        }
    }
}

void TimerMode::display() {

    lcd.clear();

    lcd.print("Timer Mode ");
    lcd.print(_state);
    if (_state == SETUP) {
        lcd.setCursor(0, 1);
        lcd.print("Set time: ");
        lcd.print(_timerDuration / 1000 / 60);
        lcd.print("mins");
    }
    if (_state == RUNNING) {

        unsigned long remainingTime = _timerDuration - _elapsedTime;
        uint32_t totalSeconds = remainingTime / 1000;
        uint16_t minutes = totalSeconds / 60;
        uint16_t seconds = totalSeconds % 60;

        lcd.setCursor(0, 1);
        lcd.print("Remaining: ");
        lcd.print(minutes);
        lcd.print("m ");
        lcd.print(seconds);
        lcd.print("s");
    }
    lcd.display();
}

unsigned long TimerMode::encoderValueToDuration(long value) {
    if (value < 0) {
       return 0;
    }

    return (value / 4) * 60 * 1000;
}
