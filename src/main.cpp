#include <Arduino.h>
#include "Cube.h"
#include <LiquidCrystal_I2C.h>


#include "Mode.h"
#include "RotaryEncoder.h"
#include <RTClib.h>
#include <ModeManager.h>
#include <ClockManager.h>
#include <ColorModule.h>
#include <RotaryEncoder.h>

// Cube representation 
Cube cube;

// Mode manager (manages mode trasitions)
ModeManager modeManager;
ClockManager clockManager;
ColorModule colorModule;

// Inputs
RotaryEncoder encoder(ENCODER_CLOCK_PIN, ENCODER_DATA_PIN, RotaryEncoder::LatchMode::FOUR3);
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

    Serial.println("Starting setup");
    setupLCD();
    setupRTC();
    Serial.println("Setup complete");
}

void loop() {
    Face face = cube.getFace();
    static int pos = 0;

    modeManager.update(face);
    clockManager.update();

    colorModule.display(modeManager.getColor());
    // Handle encoder input
    encoder.tick();

    int newPos = encoder.getPosition();
    if (pos != newPos) {
        pos = newPos;        
        int32_t returnPos = modeManager.onEncoderChange(newPos);
        if (returnPos != newPos) {
            encoder.setPosition(returnPos);
            pos = returnPos;
        }
    }

    button.update();
    ButtonEvent event = button.getEvent();
    if (event != ButtonEvent::None) {
        modeManager.onButtonEvent(event);
    }
}

