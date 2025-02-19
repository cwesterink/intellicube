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
#include <ModeManager.h>

// Pin definitions
const int SENSOR_PINS[4] = {7, 6, 5, 4};
const int BUTTON_PIN = 8;

const int ENCODER_CLOCK_PIN = 2;
const int ENCODER_DATA_PIN = 3;

// Cube representation 
Cube cube(SENSOR_PINS);

// Mode manager (manages mode trasitions)
ModeManager modeManager;

// Inputs
Encoder encoder(ENCODER_CLOCK_PIN, ENCODER_DATA_PIN);
Button button(BUTTON_PIN);
RTC_DS3231 rtc;

// 20x4 LCD Display
LiquidCrystal_I2C lcd(0x27, 20, 4);

int32_t prevEncoderPosition  = 0;

void setupLCD() {
    lcd.init();
    lcd.backlight();
    lcd.home();
    lcd.print("Loading...");
}

void setupRTC() {
    if (!rtc.begin()) {
        lcd.setCursor(0, 0);
        lcd.print("RTC NOT FOUND");
        while (1);
    }
}

void setup() {
    Wire.begin();
    Serial.begin(9600);

    setupLCD();
    setupRTC();
}

void loop() {
    
    face_t face = cube.getFace();
    
    modeManager.update(face);
    modeManager.display();

    // Handle encoder input
    int32_t encoderPosition = -1 * encoder.read();
    if (encoderPosition != prevEncoderPosition) {
        int32_t setPosition = modeManager.onEncoderChange(encoderPosition);
        if (setPosition != encoderPosition) {
            encoder.write(-setPosition);
            prevEncoderPosition = setPosition;
        } else {
            prevEncoderPosition = encoderPosition;
        }
    }

    button.update();
    ButtonEvent event = button.getEvent();
    if (event != ButtonEvent::None) {
        modeManager.onButtonEvent(event);
    }
    
    delay(50);
}

