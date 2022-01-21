/* Includes ------------------------------------------------------------------*/
#include "mbed.h"
#include <cstdint>
#include <cstdio>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define C3  131 //C octave3
#define Csharp3 139 //C#
#define D3  147 //D
#define Dsharp3 156//D#
#define E3  165 //E
#define F3  175 //F
#define Fsharp3 185 //F#
#define G3  196 //G
#define Gsharp3 208 //G#
#define A3  220 //A
#define Asharp3 233 //A#
#define B3  247 //B
#define C4  262 //C octave4
#define Csharp4 277 //C#
#define D4  294 //D
#define Dsharp4 311//D#
#define E4  330 //E
#define F4  349 //F
#define Fsharp4 370 //F#
#define G4  392 //G
#define Gsharp4 415 //G#
#define A4  440 //A
#define Asharp4 466 //A#
#define B4  494 //B
#define C5  523 //C octave5
#define Csharp5 554 //C#
#define D5  587 //D
#define Dsharp5 622//D#
#define E5  659 //E
#define F5  699 //F
#define Fsharp5 740 //F#
#define G5  784 //G
#define Gsharp5 831 //G#
#define A5  880 //A
#define Asharp5 932 //A#
#define B5  988 //B
#define C6  1047 //C octave6
#define Csharp6 1109 //C#
#define D6  1175 //D
#define Dsharp6 1245 //D#
#define E6  1319 //E
#define F6  1397 //F
#define Fsharp6 1480 //F#
#define G6  1568 //G
#define Gsharp6 1661 //G#
#define A6  1760 //A
#define Asharp6 1865 //A#
#define B6  1976 //B

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
// void Tune(PwmOut name, int period, int beat);
void PlaySong(uint8_t songId, PwmOut buzzer);

// void Auto_tunes(PwmOut name, int period, int beat);
// void Stop_tunes(PwmOut name);
        
/* Private functions ---------------------------------------------------------*/
