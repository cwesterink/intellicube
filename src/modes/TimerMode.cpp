#include "modes/TimerMode.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Pins.h"
#include "ClockManager.h"

extern ClockManager clockManager;

int32_t TimerMode::onEncoderChange(int32_t encoderVal) {
    if (!clockManager.isTimerRunning()) {
        _timerDuration = encoderValueToSeconds(encoderVal);
        if (encoderVal < 0) {
            return 0;
        }
    }
    return encoderVal;
}

void TimerMode::onButtonEvent(ButtonEvent event) {
    if (event == ButtonEvent::Click && !clockManager.isTimerRunning()) {
        clockManager.startTimer(_timerDuration);
        _timerDuration = 0;
    } else if (event == ButtonEvent::Hold && clockManager.isTimerRunning()) {
        clockManager.stopTimer();
    }
}

void TimerMode::display() {

    lcd.clear();

    lcd.print("Timer");
    if (!clockManager.isTimerRunning()) {
        lcd.setCursor(0, 1);
        lcd.print("Set time: ");
        lcd.print(_timerDuration / 60);
        lcd.print("mins");
    } else {
        uint32_t timeLeft = clockManager.getTimeLeft();

        uint16_t minutes = timeLeft / 60;
        uint16_t seconds = timeLeft % 60;

        lcd.setCursor(0, 1);
        lcd.print("Remaining: ");
        lcd.print(minutes);
        lcd.print("m ");
        lcd.print(seconds);
        lcd.print("s");
    }
}

unsigned long TimerMode::encoderValueToSeconds(long value) {
    if (value < 0) {
       return 0;
    }

    return value * 60;
}
