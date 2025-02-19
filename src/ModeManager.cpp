#include "ModeManager.h"

extern Encoder encoder;

ModeManager::ModeManager()
    : prevFace(255) {
    modes[0] = new IdleMode();
    modes[1] = new TimerMode();
    modes[2] = new HabitMode();
    modes[3] = new IdleMode();
    modes[4] = new IdleMode();
    modes[5] = new IdleMode();

    currentMode = modes[0];
}

void ModeManager::onButtonEvent(ButtonEvent event) {
    currentMode->onButtonEvent(event);
}

int32_t ModeManager::onEncoderChange(int32_t encoderVal) {
    return currentMode->onEncoderChange(encoderVal);
}

void ModeManager::update(face_t face) {
    if (face != prevFace) {
        prevFace = face;
        currentMode = modes[face];
        encoder.write(0);
    }
    currentMode->update();
}

void ModeManager::display() {
    currentMode->display();
}
