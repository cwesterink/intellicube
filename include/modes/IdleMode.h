// IdleMode.h
#ifndef IDEMODE_H
#define IDEMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

extern LiquidCrystal_I2C lcd;
extern RTC_DS3231 rtc;

class IdleMode : public Mode {
    public:
        IdleMode(): _dateStr(), _timeStr(), _message() {};
        void update() override;    // Update the timer (elapsed time)
        void display() override;   // Display the timer on the LCD

        uint16_t getRefreshRate() override { return 1000; }
        rgb_color getColor() override { return { 200, 100, 0}; }

        String getName() override { return "Idle"; }

    private:
        char _dateStr[20];
        char _timeStr[20];
        char _message[20];
};

#endif