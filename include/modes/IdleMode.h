// IdleMode.h
#ifndef IDEMODE_H
#define IDEMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include <RTClib.h>

extern LiquidCrystal_I2C lcd;
extern RTC_DS3231 rtc;

class IdleMode : public Mode {
    public:
        IdleMode() {};
        void update() override;    // Update the timer (elapsed time)
        void display() override;   // Display the timer on the LCD

    private:
        char _dateStr[20];
        char _timeStr[20];
        char _message[20];
};

#endif