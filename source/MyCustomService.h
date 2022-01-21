/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __BLE_MY_CUSTOM_SERVICE_H__
#define __BLE_MY_CUSTOM_SERVICE_H__

class MyCustomService {
public:
    const static uint16_t MY_CUSTOM_SERVICE_UUID              = 0xB000;
    const static uint16_t MY_CUSTOM_STATE_CHARACTERISTIC_UUID = 0xB001;

    MyCustomService(BLEDevice &_ble, bool initialValueForLEDCharacteristic) :
        ble(_ble), ledState(MY_CUSTOM_STATE_CHARACTERISTIC_UUID, &initialValueForLEDCharacteristic)
    {
        GattCharacteristic *charTable[] = {&ledState};
        GattService         myCustomService(MY_CUSTOM_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));

        ble.gattServer().addService(myCustomService);
    }

    GattAttribute::Handle_t getValueHandle() const
    {
        return ledState.getValueHandle();
    }

private:
    BLEDevice                         &ble;
    ReadWriteGattCharacteristic<bool> ledState;
};

#endif /* #ifndef __BLE_MY_CUSTOM_SERVICE_H__ */