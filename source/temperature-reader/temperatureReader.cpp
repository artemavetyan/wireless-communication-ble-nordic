#include <cstdint>
#include <mbed.h>
#include <stdint.h>
#include "temperatureReader.h"

TemperatureReader::TemperatureReader(AnalogIn* therm): _therm(therm) {
}

void TemperatureReader::readTemperature() {
    float thermValue;
    printf("%s\n","readTemperature");
    thermValue = _therm->read(); 
    printf("%f\n" , thermValue);

    // convert the value to resistance
    thermValue = 1 / thermValue  - 1;     // (1/ADC - 1) 
    thermValue = 10000 / thermValue;     // 10K / (1/ADC - 1)

    printf("%f\n" , thermValue);

    float steinhart = 0;
    steinhart = thermValue / 10000;      // (R/Ro)
    steinhart = log(steinhart);          // ln(R/Ro)
    steinhart /= 3950;                   // 1/B * ln(R/Ro)
    steinhart += 1.0 / (25 + 273.15);    // + (1/To)
    steinhart = 1.0 / steinhart;         // Invert
    steinhart -= 273.15;                 // convert absolute temp to C
    steinhart = steinhart/10;

    
    uint8_t valueToWrite = (uint8_t)steinhart;
    _my_custom_temperature_service->write(valueToWrite);
    //TODO: show temperature on LCD>
    // _displayer->display(steinhart);
}

void TemperatureReader::setTemperatureService(MyCustomTemperatureService* my_custom_temperature_service) {
    _my_custom_temperature_service = my_custom_temperature_service;
}
void TemperatureReader::setDisplayer(Displayer* displayer) {
    _displayer = displayer;
}



