#include <mbed.h>

#ifndef PLAYER_H // include guard
#define PLAYER_H

class Player
{

public:
    Player(PwmOut* buzzer); 

    void play(uint8_t songIndex);
private:
    // void playHappyBirthday();
    // void playWilhelmus();
    // void (*_func_ptr[2])();
    PwmOut* _buzzer;

};

#endif /* PLAYER_H */