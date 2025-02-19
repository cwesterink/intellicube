#include "modes/PormodoroMode.h"
#include "Mode.h"
#include <Arduino.h>
#include <RTClib.h>

extern LiquidCrystal_I2C lcd;
extern ClockManager clockManager;


void PomodoroMode::onButtonEvent(ButtonEvent event) {
    if (event == ButtonEvent::Click && !_isRunning) {
        startPomodoro();
    } else if (event == ButtonEvent::Hold && _isRunning) {
        stopPomodoro();
    }
}

void PomodoroMode::display() {
    lcd.clear();

    if (_isRunning) {
        uint32_t timeLeft = clockManager.getPomodoroTimeLeft();
        PomodoroState s = clockManager.getPomodoroState();
        uint32_t minutes = timeLeft / 60;
        uint32_t seconds = timeLeft % 60;
        lcd.clear();
        lcd.print("Pomodoro");
        lcd.setCursor(15, 0);
        lcd.print(s == PomodoroState::Work ? " Work" : "Break");
        lcd.setCursor(7, 2);
        lcd.print(minutes);
        lcd.print("m ");
        lcd.print(seconds);
        lcd.print("s");
    } else {
        lcd.print("Study Mode");
        lcd.setCursor(0, 1);
        lcd.print("Work: ");
        lcd.print(WORK_DURATION / 60);
        lcd.print("m");
    
        lcd.setCursor(0, 2);
        lcd.print("Break: ");
        lcd.print(BREAK_DURATION / 60);
        lcd.print("m");
    
        lcd.setCursor(6, 3);
        lcd.print("Click to start");
    }
}

void PomodoroMode::startPomodoro() {
    clockManager.startPomodoroTimer(WORK_DURATION, BREAK_DURATION);
    _isRunning = true;
}

void PomodoroMode::stopPomodoro() {
    clockManager.stopPomodoroTimer();
    _isRunning = false;
}