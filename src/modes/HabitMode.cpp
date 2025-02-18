#include "HabitMode.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


int HabitMode::onEncoderChange(int32_t encoderVal) {
    Serial.println(encoderVal);
    if (encoderVal < 0) {
        _selectedHabitId = 0;
        return 0;
    } else if (encoderVal >= (_numHabits - 1) * 4) {
        _selectedHabitId = _numHabits - 1;
        return 12;
    } else {
        _selectedHabitId = encoderVal / 4;
        return -1;
    }
}


void HabitMode::update() {}


void HabitMode::onButtonClick() {
    _habits[_selectedHabitId].completed = !_habits[_selectedHabitId].completed;
}

void HabitMode::display() {


    habit_t *listedHabits[3];
    int firstIdx;
    if (_selectedHabitId < 3) {
        firstIdx = 0;
    } else {
        firstIdx = _selectedHabitId - 2;
    }

    for (int i = 0; i < 3; i++) {
        listedHabits[i] = &_habits[firstIdx + i];
    }

    _screen.clear();

    _screen.print("-------Habits-------");

    for (int i = 0; i < 3; i++) {
        _screen.setCursor(0, i + 1);
        _screen.print(i+firstIdx == _selectedHabitId ? ">" : " ");
        
        _screen.print(listedHabits[i]->name);
        _screen.setCursor(16, i + 1);
        _screen.print(listedHabits[i]->completed ? "[X]" : "[ ]");
    }
    _screen.display();
}
