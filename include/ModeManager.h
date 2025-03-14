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
#include "modes/RelaxMode.h"

#include "Cube.h"

class ModeManager {
    public:
        ModeManager();
        void update(Face face);
        void display();

        rgb_color getColor() { return _currentMode->getColor(); }
        void onButtonEvent(ButtonEvent event);
        int32_t onEncoderChange(int32_t encoderVal);
    private:
        Face _prevFace;
        Mode* _currentMode;
};

#endif
