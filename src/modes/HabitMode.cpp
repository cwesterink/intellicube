#include "modes/HabitMode.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

int32_t HabitMode::onEncoderChange(int32_t encoderVal) {
    if (encoderVal < 0) {
        _selectedHabitId = 0;
    } else if (encoderVal >= (_numHabits - 1)) {
        _selectedHabitId = _numHabits - 1;
    } else {
        _selectedHabitId = encoderVal;
    }
    display();
    return _selectedHabitId;
}

void HabitMode::onButtonEvent(ButtonEvent event) {
    if (event == ButtonEvent::Click) {
        _habits[_selectedHabitId].completed = !_habits[_selectedHabitId].completed;
        display();
    }
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

    lcd.clear();

    lcd.print("-------Habits-------");

    for (int i = 0; i < 3; i++) {
        lcd.setCursor(0, i + 1);
        lcd.print(i+firstIdx == _selectedHabitId ? ">" : " ");
        
        lcd.print(listedHabits[i]->name);
        lcd.setCursor(16, i + 1);
        lcd.print(listedHabits[i]->completed ? "[X]" : "[ ]");
    }
    lcd.display();
}
