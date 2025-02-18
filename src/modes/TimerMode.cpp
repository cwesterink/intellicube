#include "TimerMode.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


int TimerMode::onEncoderChange(int32_t encoderVal) {
    if (_state == SETUP) {
        _timerDuration = encoderValueToDuration(encoderVal);
        if (encoderVal < 0) {
            return 0;
        }
    }
    return -1;
}


void TimerMode::update() {
    if (_state == RUNNING) {
        _elapsedTime = (millis() - _startTime);
        if (_elapsedTime >= _timerDuration) {
            _state = SETUP;
            tone(10, 1000, 2000);
        }
    }
}


void TimerMode::onButtonClick() {
    if (_state == SETUP) {
        _state = RUNNING;
        _startTime = millis();
    } else if (_state == RUNNING) {
        _state = SETUP;
    }
}

void TimerMode::display() {

    _screen.clear();

    _screen.print("Timer Mode ");
    _screen.print(_state);
    if (_state == SETUP) {
        _screen.setCursor(0, 1);
        _screen.print("Set time: ");
        _screen.print(_timerDuration / 1000 / 60);
        _screen.print("mins");
    }
    if (_state == RUNNING) {

        unsigned long remainingTime = _timerDuration - _elapsedTime;
        uint32_t totalSeconds = remainingTime / 1000;
        uint16_t minutes = totalSeconds / 60;
        uint16_t seconds = totalSeconds % 60;

        _screen.setCursor(0, 1);
        _screen.print("Remaining: ");
        _screen.print(minutes);
        _screen.print("m ");
        _screen.print(seconds);
        _screen.print("s");
    }
    _screen.display();
}

unsigned long TimerMode::encoderValueToDuration(long value) {
    if (value < 0) {
       return 0;
    }

    return (value / 4) * 60 * 1000;
}
