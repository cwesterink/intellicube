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
        void update() override {
            if (isSelected) {
                _modes[_selectedMode]->update();
            }
        }

        void onButtonEvent(ButtonEvent event) override;
        rgb_color getColor() override { return _modes[_selectedMode]->getColor(); }
        int32_t onEncoderChange(int32_t encoderVal) override;

        uint16_t getRefreshRate() override {
            if (isSelected) {
                return _modes[_selectedMode]->getRefreshRate();
            } else {
                return 0;
            }
         }

        String getName() { return _name; };

    private:
        String _name; 
        bool isSelected = false;
        uint8_t _selectedMode = 0;
        std::vector<Mode*> _modes;
        size_t _modeCount;
};


#endif // MULTIMODE_H
