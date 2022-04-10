#include <mbed.h>

#ifndef PLAYER_H // include guard
#define PLAYER_H

class Player
{

public:
    Player(PwmOut* buzzer); 

    void play(uint8_t songIndex);
private:
    PwmOut* _buzzer;
};

#endif /* PLAYER_H */