#ifndef MULTIMODE_H
#define MULTIMODE_H

#include <Arduino.h>
#include "Mode.h"
#include <LiquidCrystal_I2C.h>
#include <ArduinoSTL.h>
#include <vector>
#include <Cube.h>


class MultiMode : public Mode {
    public:
        MultiMode(String name, std::vector<Mode*> modes) 
            : _name(name), _modes(std::vector<Mode*>(modes)), _modeCount(modes.size()) {};

        void display() override;
        void onButtonEvent(ButtonEvent event) override;
        int32_t onEncoderChange(int32_t encoderVal) override;

        String getName() { return _name; };

    private:
        String _name; 
        bool isSelected = false;
        face_t _selectedMode = 0;
        std::vector<Mode*> _modes;
        size_t _modeCount;
};


#endif // MULTIMODE_H
