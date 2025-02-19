#ifndef POMODORO_MODE_H
#define POMODORO_MODE_H

#include "Mode.h"
#include "ClockManager.h"

class PomodoroMode : public Mode {
public:
    PomodoroMode() {};

    // void update() override;
    void display() override;

    // int32_t onEncoderChange(int32_t encoderVal) override;
    void onButtonEvent(ButtonEvent event) override;

private:
    int WORK_DURATION = 150;  // Default 25 min
    int BREAK_DURATION = 30;  // Default 5 min
    bool _isRunning = false;

    void startPomodoro();
    void stopPomodoro();
};

#endif
