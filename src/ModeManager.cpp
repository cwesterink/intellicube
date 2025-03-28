#include "ModeManager.h"
#include "RotaryEncoder.h"

extern RotaryEncoder encoder;

// Declare your modes somewhere globally or in setup
IdleMode idleMode;
GameMode gameMode;
HabitMode habitMode;
RelaxMode relaxMode;

PomodoroMode pomodoroMode;
TimerMode defaultTimerMode;

std::vector<Mode*> timerModes = {&pomodoroMode, &defaultTimerMode};

MultiMode timerMode("Timer", timerModes);
SettingsMode settingsMode;

// HOME,
// TIMER,
// HABIT,
// GAME,
// RELAX,
// SETTINGS
Mode* modes[6] = {
    &idleMode,
    &timerMode,
    &habitMode,
    &gameMode,
    &relaxMode,
    &settingsMode
};

Mode* getMode(Face face) {
    return modes[static_cast<int>(face)];
}

ModeManager::ModeManager()
    : _prevFace(Face::HOME), _currentMode(getMode(Face::HOME)) {}

void ModeManager::onButtonEvent(ButtonEvent event) {
    _currentMode->onButtonEvent(event);
}

int32_t ModeManager::onEncoderChange(int32_t encoderVal) {
    return _currentMode->onEncoderChange(encoderVal);
}

void ModeManager::update(Face face) {

    bool isFaceChanged = (face != _prevFace);
    if (isFaceChanged) {
        _prevFace = face;
        _currentMode = getMode(face);
        encoder.setPosition(0);
    }

    if (isFaceChanged || millis() - _lastRefreshTime > _currentMode->getRefreshRate()) {
        _currentMode->update();
        _currentMode->display();
        _lastRefreshTime = millis();
    }
}
