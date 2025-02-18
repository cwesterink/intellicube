#include "IdleMode.h"
#include "Mode.h"
#include <Arduino.h>
#include <RTClib.h>

const char* dayOfWeek(int d) {
    const char* days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return days[d];
}

const char* monthAbbrev(int m) {
    const char* months[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                            "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    return months[m - 1]; // Adjust for 1-based month numbering
}

void IdleMode::update() {

    // Update the idle mode logic
    DateTime now = _rtc.now();
    
    uint8_t hr = now.hour();

    uint8_t hour12 = hr % 12;
    if (hour12 == 0) hour12 = 12;
    const char* ampm = (hr < 12) ? "AM" : "PM";

    snprintf(_dateStr, sizeof(_dateStr), "%s  %02d-%s-%02d",
             dayOfWeek(now.dayOfTheWeek()), now.day(), monthAbbrev(now.month()), now.year());
    
    snprintf(_timeStr, sizeof(_timeStr), "    %02d : %02d %s   ", hour12, now.minute(), ampm);

    if (hr < 12) {
        snprintf(_message, sizeof(_message), "Good Morning!");
    } else if (hr < 18) {
        snprintf(_message, sizeof(_message), "Good Afternoon!");
    } else {
        snprintf(_message, sizeof(_message), "Good Evening!");
    }
}


void IdleMode::display() {
    // Display the idle mode on the LCD
    _screen.clear();
    // Display on LCD
    _screen.clear();
    _screen.setCursor(2, 0); _screen.print(_dateStr);
    _screen.setCursor(2, 1); _screen.print(_timeStr);
    _screen.setCursor(0, 2); _screen.print("--------------------");

    _screen.setCursor(4, 3); _screen.print(_message);
}
