#include "modes/RelaxMode.h"
#include <LiquidCrystal_I2C.h>

// Assuming you have access to the global lcd object
extern LiquidCrystal_I2C lcd;

int32_t RelaxMode::onEncoderChange(int32_t encoderVal) {
    _refreshRate = constrain(250 + encoderVal * 10, 150, 350);
    return constrain(encoderVal, -10, 10);
}

void RelaxMode::display() {
    
    lcd.clear();  // Clear the screen before rendering the next frame

    // Generate random positions for raindrops
    int randomPos = random(0, 20);  // Get a random horizontal position
    _dropPositions[randomPos] = 0;   // Create a raindrop at that position

    // Move all raindrops down
    for (int i = 0; i < 20; i++) {
        if (_dropPositions[i] >= 0) {
            lcd.setCursor(i, _dropPositions[i]);
            lcd.print("|");  // Draw the raindrop
            _dropPositions[i]++;  // Move raindrop down
            if (_dropPositions[i] > 3) {
                _dropPositions[i] = -1;  // Reset raindrop after it leaves the screen
            }
        }
    }
}