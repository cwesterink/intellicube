#include <Arduino.h>
#include "Cube.h"
#include "test.h"
#include <Encoder.h>
#include <LiquidCrystal_I2C.h>
#include "modes/TimerMode.h"
#include "modes/IdleMode.h"
#include "modes/HabitMode.h"

#include "Mode.h"
#include <RTClib.h>

const int SENSOR_PINS[4] = {7, 6, 5, 4};
const int BUTTON_PIN = 8;

const int ENCODER_CLOCK_PIN = 2;
const int ENCODER_DATA_PIN = 3;

Cube cube(SENSOR_PINS);
Encoder encoder(ENCODER_CLOCK_PIN, ENCODER_DATA_PIN);
Button button(BUTTON_PIN);
LiquidCrystal_I2C screen(0x27, 20, 4);

RTC_DS3231 rtc;



Mode* modes[6] = {
    new IdleMode(screen, rtc),
    new TimerMode(screen),
    new HabitMode(screen),
    new IdleMode(screen, rtc),
    new IdleMode(screen, rtc),
    new IdleMode(screen, rtc)
};

Mode *currentMode;

int32_t prevEncoderPosition  = 0;

face_t prevFace = 5;
face_t face = 5;

void setupScreen() {
    screen.init();
    screen.backlight();
    screen.home();
    screen.print("Hello, world!");
}

void setup() {
    Wire.begin();
    Serial.begin(9600); // starts serial communication at 9,600 baud (the rate)
    setupScreen();

    if (!rtc.begin()) {
        screen.setCursor(0, 0);
        screen.print("RTC NOT FOUND");
        while (1);
    }

    currentMode = new IdleMode(screen, rtc);
}

void loop() {

    face = cube.getFace();
    if (face != prevFace) {
        Serial.print("Face: ");
        Serial.println(face);
        prevFace = face;

        currentMode = modes[face];
    }

    int32_t encoderPosition = -1 * encoder.read();
    if (encoderPosition != prevEncoderPosition) {
        int newPosition = currentMode->onEncoderChange(encoderPosition);
        if (newPosition != -1) {
            encoder.write(-newPosition);
            prevEncoderPosition = newPosition;
        } else {
            prevEncoderPosition = encoderPosition;
        }
    }

    if (button.isPressed()) {
        currentMode->onButtonClick();
    }

    for (size_t i = 0; i < 6; i++)
    {
        modes[i]->update();
    }
    
    // currentMode->update();
    currentMode->display();
    // Serial.println(face);
    delay(50); // slow the loop down a bit before it repeats
}

