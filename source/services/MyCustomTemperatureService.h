#ifndef __BLE_MY_CUSTOM_TEMPERATURE_SERVICE_H__
#define __BLE_MY_CUSTOM_TEMPERATURE_SERVICE_H__

#include <stdint.h>
#include "ble/BLE.h"

class MyCustomTemperatureService {
public:
    const static uint16_t MY_CUSTOM_TEMPERATURE_SERVICE_UUID              = 0xD000;
    const static uint16_t MY_CUSTOM_TEMPERATURE_STATE_CHARACTERISTIC_UUID = 0xD001;

    MyCustomTemperatureService(BLEDevice &_ble, int initialValueForTemperatureCharacteristic) :
        ble(_ble), temperatureState(MY_CUSTOM_TEMPERATURE_STATE_CHARACTERISTIC_UUID, &initialValueForTemperatureCharacteristic, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY)
    {
        GattCharacteristic *charTable[] = {&temperatureState};
        GattService         myCustomTemperatureService(MY_CUSTOM_TEMPERATURE_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));

        ble.gattServer().addService(myCustomTemperatureService);
    }

    GattAttribute::Handle_t getValueHandle() const
    {
        return temperatureState.getValueHandle();
    }

    void write(uint8_t &value) {
        ble.gattServer().write(temperatureState.getValueHandle(), &value, sizeof(value));
    }

private:
    BLEDevice                         &ble;
    ReadWriteGattCharacteristic<int> temperatureState;

};

#endif /* #ifndef __BLE_MY_CUSTOM_TEMPERATURE_SERVICE_H__ */
