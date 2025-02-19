#ifndef CLOCK_MANAGER_H
#define CLOCK_MANAGER_H

#include <Arduino.h>
#include <RTClib.h>

extern RTC_DS3231 rtc;

enum class PomodoroState { Work, Break, Idle };

class ClockManager {
public:
    ClockManager();

    // Regular Timer Functions
    void startTimer(uint32_t durationSec);
    void stopTimer();
    bool isTimerRunning();
    uint32_t getTimeLeft();

    // Pomodoro Timer Functions
    void startPomodoroTimer(uint32_t workDurationSec, uint32_t breakDurationSec);
    void stopPomodoroTimer();
    bool isPomodoroRunning();
    PomodoroState getPomodoroState();
    uint32_t getPomodoroTimeLeft();

    // General Update Function
    void update();

private:

    // Regular Timer
    DateTime regularTimerEnd;
    bool regularTimerRunning;

    // Pomodoro Timer
    DateTime pomodoroEnd;
    uint32_t workDuration;
    uint32_t breakDuration;
    bool pomodoroRunning;
    PomodoroState pomodoroState;

    void checkTimers();  // Handles timer completion
};

#endif
