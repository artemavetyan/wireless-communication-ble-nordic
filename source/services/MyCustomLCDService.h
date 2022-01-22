#ifndef __BLE_MY_CUSTOM_LCD_SERVICE_H__
#define __BLE_MY_CUSTOM_LCD_SERVICE_H__

class MyCustomLCDService {
public:
    const static uint16_t MY_CUSTOM_LCD_SERVICE_UUID              = 0xC000;
    const static uint16_t MY_CUSTOM_LCD_STATE_CHARACTERISTIC_UUID = 0xC001;

    MyCustomLCDService(BLEDevice &_ble, char initialValueForLCDCharacteristic) :
        ble(_ble), lcdState(MY_CUSTOM_LCD_STATE_CHARACTERISTIC_UUID, &initialValueForLCDCharacteristic)
    {
        GattCharacteristic *charTable[] = {&lcdState};
        GattService         myCustomLCDService(MY_CUSTOM_LCD_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));

        ble.gattServer().addService(myCustomLCDService);
    }

    GattAttribute::Handle_t getValueHandle() const
    {
        return lcdState.getValueHandle();
    }

private:
    BLEDevice                         &ble;
    // ReadWriteGattCharacteristic<bool> lcdState;
    ReadWriteArrayGattCharacteristic<char, 16> lcdState;

};

#endif /* #ifndef __BLE_MY_CUSTOM_LCD_SERVICE_H__ */
