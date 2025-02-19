#ifndef POMODORO_MODE_H
#define POMODORO_MODE_H

#include "Mode.h"
#include "ClockManager.h"

class PomodoroMode : public Mode {
public:
    PomodoroMode() {};

    void display() override;
    void onButtonEvent(ButtonEvent event) override;

private:
    int WORK_DURATION = 150;  // Default 25 min
    int BREAK_DURATION = 30;  // Default 5 min
};

#endif
