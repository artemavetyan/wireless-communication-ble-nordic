#include <mbed.h>
#include "LiquidCrystal_I2C.h"

#ifndef DISPLAYER_H // include guard
#define DISPLAYER_H

class Displayer
{

public:
    Displayer(LiquidCrystal_I2C* lcd); 

    void display(char message[], int length);
    void display(float value);

private:
    LiquidCrystal_I2C* _lcd;

};

#endif /* DISPLAYER_H */