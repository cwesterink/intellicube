#ifndef POMODORO_MODE_H
#define POMODORO_MODE_H

#include "Mode.h"
#include "ClockManager.h"

class PomodoroMode : public Mode {
public:
    PomodoroMode() {};

    void display() override;
    void update() override { display(); }
    void onButtonEvent(ButtonEvent event) override;

    uint16_t getRefreshRate() override;

    rgb_color getColor() override { return rgb_color(255, 128, 0); }
    String getName() override { return "Study Timer"; }

private:
    int WORK_DURATION = 150;  // Default 25 min
    int BREAK_DURATION = 30;  // Default 5 min
};

#endif
