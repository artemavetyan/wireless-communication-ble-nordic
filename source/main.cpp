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

#include <cstdint>
#include <events/mbed_events.h>
#include <mbed.h>
#include "ble/BLE.h"
#include "LEDService.h"
#include "MyCustomService.h"
#include "my_tone.h"
#include "player.h"

#include "pretty_printer.h"

I2C i2c_lcd(PTE0,PTE1); // SDA, SCL

const static char DEVICE_NAME[] = "MyCoolName";

PwmOut buzzer(P1_14);

int eventId;


static EventQueue event_queue(/* event count */ 10 * EVENTS_EVENT_SIZE);

class LEDDemo : ble::Gap::EventHandler {
public:
    LEDDemo(BLE &ble, events::EventQueue &event_queue) :
        _ble(ble),
        _event_queue(event_queue),
        _alive_led(LED1, 1),
        _actuated_led(LED2, 0),
        _led_uuid(LEDService::LED_SERVICE_UUID),
        _led_service(NULL),
        _my_custom_service_uuid(MyCustomService::MY_CUSTOM_SERVICE_UUID),
        _my_custom_service(NULL),
        _player(&buzzer),
        _adv_data_builder(_adv_buffer) {}

    ~LEDDemo() {
        delete _led_service;
        delete _my_custom_service;

    }

    void start() {
        _ble.gap().setEventHandler(this);

        _ble.init(this, &LEDDemo::on_init_complete);

        // _event_queue.call_every(500, this, &LEDDemo::blink);

        _event_queue.dispatch_forever();
    }

private:
    /** Callback triggered when the ble initialization process has finished */
    void on_init_complete(BLE::InitializationCompleteCallbackContext *params) {
        if (params->error != BLE_ERROR_NONE) {
            printf("Ble initialization failed.");
            return;
        }

        _led_service = new LEDService(_ble, false);
        _my_custom_service = new MyCustomService(_ble, false);

        _ble.gattServer().onDataWritten(this, &LEDDemo::on_data_written);

        print_mac_address();

        start_advertising();
    }

    void start_advertising() {
        /* Create advertising parameters and payload */

        ble::AdvertisingParameters adv_parameters(
            ble::advertising_type_t::CONNECTABLE_UNDIRECTED,
            ble::adv_interval_t(ble::millisecond_t(1000))
        );
        

        _adv_data_builder.setFlags();
        _adv_data_builder.setLocalServiceList(mbed::make_Span(&_my_custom_service_uuid, 1));
        _adv_data_builder.setName(DEVICE_NAME);

        /* Setup advertising */

        ble_error_t error = _ble.gap().setAdvertisingParameters(
            ble::LEGACY_ADVERTISING_HANDLE,
            adv_parameters
        );

        if (error) {
            printf("_ble.gap().setAdvertisingParameters() failed\r\n");
            return;
        }

        error = _ble.gap().setAdvertisingPayload(
            ble::LEGACY_ADVERTISING_HANDLE,
            _adv_data_builder.getAdvertisingData()
        );

        if (error) {
            printf("_ble.gap().setAdvertisingPayload() failed\r\n");
            return;
        }

        /* Start advertising */

        error = _ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);

        if (error) {
            printf("_ble.gap().startAdvertising() failed\r\n");
            return;
        }
    }

    /**
     * This callback allows the LEDService to receive updates to the ledState Characteristic.
     *
     * @param[in] params Information about the characterisitc being updated.
     */ 
    void on_data_written(const GattWriteCallbackParams *params) {
        if ((params->handle == _led_service->getValueHandle()) && (params->len == 1)) {
            printf("Value received\n");
            _actuated_led = *(params->data);
        }
        if ((params->handle == _my_custom_service->getValueHandle()) && (params->len == 1)) {
            printf("Custom service\n");
            printf("%i\n",*(params->data));
            uint8_t songIndex = *(params->data);
            _player.play(songIndex);
        }
    }

    void blink() {
        _alive_led = !_alive_led;
    }

private:
    /* Event handler */

    void onConnectionComplete(const ble::ConnectionCompleteEvent&) {
       eventId = _event_queue.call_every(500, this, &LEDDemo::blink);

    }

    void onDisconnectionComplete(const ble::DisconnectionCompleteEvent&) {
        _event_queue.cancel(eventId);
        _ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);
    }

private:
    BLE &_ble;
    events::EventQueue &_event_queue;
    DigitalOut _alive_led;
    DigitalOut _actuated_led;

    Player _player;


    UUID _led_uuid;
    UUID _my_custom_service_uuid;
    LEDService *_led_service;
    MyCustomService *_my_custom_service;

    uint8_t _adv_buffer[ble::LEGACY_ADVERTISING_MAX_SIZE];
    ble::AdvertisingDataBuilder _adv_data_builder;
};

/** Schedule processing of events from the BLE middleware in the event queue. */
void schedule_ble_events(BLE::OnEventsToProcessCallbackContext *context) {
    event_queue.call(Callback<void()>(&context->ble, &BLE::processEvents));
}

int main()
{
    BLE &ble = BLE::Instance();
    ble.onEventsToProcess(schedule_ble_events);

    LEDDemo demo(ble, event_queue);
    demo.start();

    return 0;
}

