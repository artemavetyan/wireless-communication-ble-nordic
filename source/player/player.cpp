#include <mbed.h>
#include "player.h"
#include "my_tone.h"
#include <cstdio>

void playHappyBirthday(PwmOut* buzzer) {
    
    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(333);
    buzzer->write(0);

    ThisThread::sleep_for(10);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(167);
    buzzer->write(0);

    buzzer->period(1.0/A4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/C5);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/B4);
    buzzer->write(0.5);
    ThisThread::sleep_for(750);
    buzzer->write(0);

    ThisThread::sleep_for(250);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(333);
    buzzer->write(0);

    ThisThread::sleep_for(10);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(167);
    buzzer->write(0);

    buzzer->period(1.0/A4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/D5);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/C5);
    buzzer->write(0.5);
    ThisThread::sleep_for(750);
    buzzer->write(0);

    ThisThread::sleep_for(250);


    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(333);
    buzzer->write(0);

    ThisThread::sleep_for(10);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(167);
    buzzer->write(0);

    buzzer->period(1.0/G5);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/E5);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/C5);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/B4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/A4);
    buzzer->write(0.5);
    ThisThread::sleep_for(750);
    buzzer->write(0);
    
    ThisThread::sleep_for(750);

    buzzer->period(1.0/F5);
    buzzer->write(0.5);
    ThisThread::sleep_for(333);
    buzzer->write(0);

    ThisThread::sleep_for(10);

    buzzer->period(1.0/F5);
    buzzer->write(0.5);
    ThisThread::sleep_for(167);
    buzzer->write(0);

    buzzer->period(1.0/E5);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/C5);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/D5);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/C5);
    buzzer->write(0.5);
    ThisThread::sleep_for(1000);
    buzzer->write(0);
}

void playWilhelmus(PwmOut* buzzer) {
    
    for (int i = 0; i < 2; i++) {
        buzzer->period(1.0/C4);
        buzzer->write(0.5);
        ThisThread::sleep_for(500);
        buzzer->write(0);
        buzzer->period(1.0/F4);
        buzzer->write(0.5);
        ThisThread::sleep_for(500);
        buzzer->write(0);

        ThisThread::sleep_for(10);

        buzzer->period(1.0/F4);
        buzzer->write(0.5);
        ThisThread::sleep_for(500);
        buzzer->write(0);

        buzzer->period(1.0/G4);
        buzzer->write(0.5);
        ThisThread::sleep_for(250);
        buzzer->write(0);

        buzzer->period(1.0/A4);
        buzzer->write(0.5);
        ThisThread::sleep_for(250);
        buzzer->write(0);

        buzzer->period(1.0/Asharp4);
        buzzer->write(0.5);
        ThisThread::sleep_for(250);
        buzzer->write(0);

        buzzer->period(1.0/G4);
        buzzer->write(0.5);
        ThisThread::sleep_for(250);
        buzzer->write(0);

        buzzer->period(1.0/A4);
        buzzer->write(0.5);
        ThisThread::sleep_for(500);
        buzzer->write(0);

        buzzer->period(1.0/G4);
        buzzer->write(0.5);
        ThisThread::sleep_for(250);
        buzzer->write(0);

        buzzer->period(1.0/A4);
        buzzer->write(0.5);
        ThisThread::sleep_for(250);
        buzzer->write(0);

        buzzer->period(1.0/Asharp4);
        buzzer->write(0.5);
        ThisThread::sleep_for(500);
        buzzer->write(0);

        buzzer->period(1.0/A4);
        buzzer->write(0.5);
        ThisThread::sleep_for(500);
        buzzer->write(0);

        buzzer->period(1.0/G4);
        buzzer->write(0.5);
        ThisThread::sleep_for(250);
        buzzer->write(0);

        buzzer->period(1.0/F4);
        buzzer->write(0.5);
        ThisThread::sleep_for(250);
        buzzer->write(0);

        buzzer->period(1.0/G4);
        buzzer->write(0.5);
        ThisThread::sleep_for(500);
        buzzer->write(0);

        buzzer->period(1.0/F4);
        buzzer->write(0.5);
        ThisThread::sleep_for(1000);
        buzzer->write(0);

        ThisThread::sleep_for(500);
    }
    buzzer->period(1.0/A4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/Asharp4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/C5);
    buzzer->write(0.5);
    ThisThread::sleep_for(1000);
    buzzer->write(0);

    buzzer->period(1.0/D5);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/C5);
    buzzer->write(0.5);
    ThisThread::sleep_for(1000);
    buzzer->write(0);

    buzzer->period(1.0/Asharp4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/A4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/A4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/Asharp4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/A4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/F4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(750);
    buzzer->write(0);

    ThisThread::sleep_for(250);

    buzzer->period(1.0/C4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/F4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/E4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/F4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/A4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/G4);
    buzzer->write(0.5);
    ThisThread::sleep_for(1000);
    buzzer->write(0);

    buzzer->period(1.0/F4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/E4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/C4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/D4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/E4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/F4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    ThisThread::sleep_for(10);

    buzzer->period(1.0/F4);
    buzzer->write(0.5);
    ThisThread::sleep_for(250);
    buzzer->write(0);

    buzzer->period(1.0/F4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/E4);
    buzzer->write(0.5);
    ThisThread::sleep_for(500);
    buzzer->write(0);

    buzzer->period(1.0/F4);
    buzzer->write(0.5);
    ThisThread::sleep_for(1250);
    buzzer->write(0);
}

void (*songs[2]) (PwmOut* buzzer) = {playHappyBirthday, playWilhelmus};

Player::Player(PwmOut* buzzer): _buzzer(buzzer) {}

void Player::play(uint8_t songIndex) {
    
    printf("%i\n",songIndex);
    songs[songIndex](_buzzer);
}
