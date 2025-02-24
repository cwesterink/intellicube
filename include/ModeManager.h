#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

#include "Mode.h"
#include "modes/IdleMode.h"
#include "modes/TimerMode.h"
#include "modes/HabitMode.h"
#include "modes/PormodoroMode.h"
#include "modes/GameMode.h"
#include "modes/SettingsMode.h"
#include "modes/MuliMode.h"

#include "Cube.h"

class ModeManager {
public:
    ModeManager();
    void update(face_t face);
    void display();

    void onButtonEvent(ButtonEvent event);
    int32_t onEncoderChange(int32_t encoderVal);
private:
    Mode* modes[6];
    Mode* currentMode;
    face_t prevFace;
};

#endif
