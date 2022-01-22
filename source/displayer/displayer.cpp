#include <mbed.h>
#include "displayer.h"
// #include <cstdio>

Displayer::Displayer(LiquidCrystal_I2C* lcd): _lcd(lcd) {
    _lcd->init();
    _lcd->backlight();
    _lcd->print("Welcome!");
}

// void Displayer::display(char* message) {
//     printf("%s\n","here");
//     printf("%s\n",message);
//     _lcd->print("test");
// }

void Displayer::display(char message[]) {
    printf("%s\n","here");
    _lcd->clear();
    _lcd->print(message);
}

