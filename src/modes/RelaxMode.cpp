#include "modes/RelaxMode.h"
#include <LiquidCrystal_I2C.h>

// Assuming you have access to the global lcd object
extern LiquidCrystal_I2C lcd;

void RelaxMode::display() {
    static int dropPositions[20] = {-1};  // Initialize all positions to -1 (no raindrop)
    
    lcd.clear();  // Clear the screen before rendering the next frame

    // Generate random positions for raindrops
    int randomPos = random(0, 20);  // Get a random horizontal position
    dropPositions[randomPos] = 0;   // Create a raindrop at that position

    // Move all raindrops down
    for (int i = 0; i < 20; i++) {
        if (dropPositions[i] >= 0) {
            lcd.setCursor(i, dropPositions[i]);
            lcd.print("|");  // Draw the raindrop
            dropPositions[i]++;  // Move raindrop down
            if (dropPositions[i] > 3) {
                dropPositions[i] = -1;  // Reset raindrop after it leaves the screen
            }
        }
    }

    // You can add a delay to control the animation speed
    delay(150);  // Adjust the speed of the raindrops
}