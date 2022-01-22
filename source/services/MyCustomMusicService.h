#ifndef __BLE_MY_CUSTOM_MUSIC_SERVICE_H__
#define __BLE_MY_CUSTOM_MUSIC_SERVICE_H__

class MyCustomMusicService {
public:
    const static uint16_t MY_CUSTOM_MUSIC_SERVICE_UUID              = 0xB000;
    const static uint16_t MY_CUSTOM_MUSIC_STATE_CHARACTERISTIC_UUID = 0xB001;

    MyCustomMusicService(BLEDevice &_ble, bool initialValueForMusicCharacteristic) :
        ble(_ble), musicState(MY_CUSTOM_MUSIC_STATE_CHARACTERISTIC_UUID, &initialValueForMusicCharacteristic)
    {
        GattCharacteristic *charTable[] = {&musicState};
        GattService         myCustomMusicService(MY_CUSTOM_MUSIC_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));

        ble.gattServer().addService(myCustomMusicService);
    }

    GattAttribute::Handle_t getValueHandle() const
    {
        return musicState.getValueHandle();
    }

private:
    BLEDevice                         &ble;
    ReadWriteGattCharacteristic<bool> musicState;
};

#endif /* #ifndef __BLE_MY_CUSTOM_MUSIC_SERVICE_H__ */
