#include "ClockManager.h"

ClockManager::ClockManager()
    : regularTimerRunning(false), pomodoroRunning(false),
      pomodoroState(PomodoroState::Idle) {}

// ---------- REGULAR TIMER FUNCTIONS ----------

void ClockManager::startTimer(uint32_t durationSec) {
    DateTime now = rtc.now();
    regularTimerEnd = now + TimeSpan(durationSec); // Set end time
    regularTimerRunning = true;
}

void ClockManager::stopTimer() {
    regularTimerRunning = false;
}

bool ClockManager::isTimerRunning() {
    return regularTimerRunning;
}

uint32_t ClockManager::getTimeLeft() {
    if (!regularTimerRunning) return 0;
    DateTime now = rtc.now();
    return (now >= regularTimerEnd) ? 0 : (regularTimerEnd.unixtime() - now.unixtime());
}

// ---------- POMODORO TIMER FUNCTIONS ----------

void ClockManager::startPomodoroTimer(uint32_t workDurationSec, uint32_t breakDurationSec) {
    DateTime now = rtc.now();
    workDuration = workDurationSec;
    breakDuration = breakDurationSec;
    pomodoroEnd = now + TimeSpan(workDuration);
    pomodoroState = PomodoroState::Work;
    pomodoroRunning = true;
}

void ClockManager::stopPomodoroTimer() {
    pomodoroRunning = false;
    pomodoroState = PomodoroState::Idle;
}

bool ClockManager::isPomodoroRunning() {
    return pomodoroRunning;
}

PomodoroState ClockManager::getPomodoroState() {
    return pomodoroState;
}

uint32_t ClockManager::getPomodoroTimeLeft() {
    if (!pomodoroRunning) return 0;
    DateTime now = rtc.now();
    return (now >= pomodoroEnd) ? 0 : (pomodoroEnd.unixtime() - now.unixtime());
}

// ---------- UPDATE FUNCTION ----------

void ClockManager::update() {
    checkTimers();
}

void ClockManager::checkTimers() {
    DateTime now = rtc.now();

    // Check Regular Timer
    if (regularTimerRunning && now >= regularTimerEnd) {
        regularTimerRunning = false;
        Serial.println("Regular timer finished!");
        tone(10, 1000, 2000);
    }

    // Check Pomodoro Timer
    if (pomodoroRunning && now >= pomodoroEnd) {
        if (pomodoroState == PomodoroState::Work) {
            // Switch to Break
            pomodoroState = PomodoroState::Break;
            pomodoroEnd = now + TimeSpan(breakDuration);
            Serial.println("Pomodoro work session complete! Break time.");
            tone(10, 750, 2000);
        } else {
            // Switch back to Work
            pomodoroState = PomodoroState::Work;
            pomodoroEnd = now + TimeSpan(workDuration);
            Serial.println("Pomodoro break complete! Back to work.");
            tone(10, 500, 2000);
        }
    }
}
