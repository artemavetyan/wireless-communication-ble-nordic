#include <mbed.h>
#include "displayer.h"

Displayer::Displayer(LiquidCrystal_I2C* lcd): _lcd(lcd) {
    _lcd->init();
    _lcd->backlight();
    _lcd->print("Welcome!");
}

void Displayer::display(char message[], int length) {
    // TODO: bug - cant print more than 16 characters
    _lcd->clear();
    _lcd->setCursor(0, 0);

    _lcd->print(message);
}

void Displayer::display(float value) {
    _lcd->clear();
    _lcd->print(value);
}

