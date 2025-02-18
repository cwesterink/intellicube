// IdleMode.h
#ifndef IDEMODE_H
#define IDEMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include <RTClib.h>

class IdleMode : public Mode {
    public:
        IdleMode(LiquidCrystal_I2C &screen, RTC_DS3231 &rtc)
            : Mode(screen), _screen(screen), _rtc(rtc) {}
        void update() override;    // Update the timer (elapsed time)
        void display() override;   // Display the timer on the LCD

    private:
        LiquidCrystal_I2C &_screen;  // LCD screen
        RTC_DS3231 &_rtc;
        char _dateStr[20];
        char _timeStr[20];
        char _message[20];
};

#endif