#include <mbed.h>
#include "MyCustomTemperatureService.h"
#include "displayer.h"

#ifndef TEMPERATURE_READER_H // include guard
#define TEMPERATURE_READER_H

class TemperatureReader
{

public:
    TemperatureReader(AnalogIn* therm); 

    void readTemperature();
    
    void setTemperatureService(MyCustomTemperatureService* my_custom_temperature_service);
    void setDisplayer(Displayer* displayer);


private:
    AnalogIn* _therm;
    MyCustomTemperatureService *_my_custom_temperature_service;
    Displayer *_displayer;
};

#endif /* TEMPERATURE_READER_H */