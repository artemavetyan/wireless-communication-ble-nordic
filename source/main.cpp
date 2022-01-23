#include <cstdint>
#include <events/mbed_events.h>
#include <mbed.h>
#include "LiquidCrystal_I2C.h"
#include "ble/BLE.h"

#include "MyCustomMusicService.h"
#include "MyCustomLCDService.h"
#include "MyCustomTemperatureService.h"

#include "my_tone.h"
#include "player.h"
#include "displayer.h"
#include "temperatureReader.h"

#include "pretty_printer.h"

const static char DEVICE_NAME[] = "MyCoolName";

PwmOut buzzer(P1_14);
LiquidCrystal_I2C lcd(0x27, 16, 2, I2C_SDA0, I2C_SCL0);
AnalogIn therm(A1);

int blinkEventId;

int temperatureEventId;

static EventQueue event_queue(/* event count */ 10 * EVENTS_EVENT_SIZE);

class MyDemo : ble::Gap::EventHandler {
public:
    MyDemo(BLE &ble, events::EventQueue &event_queue) :
        _ble(ble),
        _event_queue(event_queue),
        _alive_led(LED1, 1),
        _actuated_led(LED2, 0),
        
        _my_custom_music_service_uuid(MyCustomMusicService::MY_CUSTOM_MUSIC_SERVICE_UUID),
        _my_custom_music_service(NULL),
        
        _my_custom_lcd_service_uuid(MyCustomLCDService::MY_CUSTOM_LCD_SERVICE_UUID),
        _my_custom_lcd_service(NULL),

        _my_custom_temperature_service_uuid(MyCustomTemperatureService::MY_CUSTOM_TEMPERATURE_SERVICE_UUID),
        _my_custom_temperature_service(NULL),
        
        _player(&buzzer),
        _displayer(&lcd),
        _temperatureReader(&therm),
        _adv_data_builder(_adv_buffer) {}

    ~MyDemo() {
        delete _my_custom_music_service;
        delete _my_custom_lcd_service;
        delete _my_custom_temperature_service;
    }

    void start() {
        _ble.gap().setEventHandler(this);

        _ble.init(this, &MyDemo::on_init_complete);

        _event_queue.dispatch_forever();
    }

private:
    /**
     * Helper that construct an event handler from a member function of this
     * instance.
     */
    template<typename Arg>
    FunctionPointerWithContext<Arg> as_cb(void (MyDemo::*member)(Arg))
    {
        return makeFunctionPointer(this, member);
    }
    /** Callback triggered when the ble initialization process has finished */
    void on_init_complete(BLE::InitializationCompleteCallbackContext *params) {
        if (params->error != BLE_ERROR_NONE) {
            printf("Ble initialization failed.");
            return;
        }

        _my_custom_music_service = new MyCustomMusicService(_ble, false);
        _my_custom_lcd_service = new MyCustomLCDService(_ble, NULL);
        _my_custom_temperature_service = new MyCustomTemperatureService(_ble, NULL);

        _temperatureReader.setTemperatureService(_my_custom_temperature_service);
        _temperatureReader.setDisplayer(&_displayer);

        _ble.gattServer().onDataWritten(this, &MyDemo::on_data_written);
        _ble.gattServer().onDataRead(this, &MyDemo::on_data_read);
        _ble.gattServer().onUpdatesEnabled(as_cb(&MyDemo::on_updates_enabled));
        // _ble.gattServer().onUpdatesDisabled(this, &MyDemo::on_updates_disabled);

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
        _adv_data_builder.setLocalServiceList(mbed::make_Span(&_my_custom_music_service_uuid, 1));
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
     * This callback allows the services to receive updates to their haracteristics.
     *
     * @param[in] params Information about the characterisitc being updated.
     */ 
    void on_data_written(const GattWriteCallbackParams *params) {
        if ((params->handle == _my_custom_music_service->getValueHandle()) && (params->len == 1)) {
            printf("Custom music service\n");
            printf("%i\n",*(params->data));
            uint8_t songIndex = *(params->data);
            _player.play(songIndex);

            _temperatureReader.readTemperature();

        }

        if ((params->handle == _my_custom_lcd_service->getValueHandle())) {
            printf("Custom LCD service\n");
            printf("Data received: length = %d, data = ",params->len);
            char message[16] = {};
            for(int x=0; x < params->len; x++) {
                printf("%c", params->data[x]);
                message[x] = params->data[x];
            }
            printf("\n\r");
            _displayer.display(message);
        }
    }

    void on_data_read(const GattReadCallbackParams *params){
        printf("Reading Data\n");
            printf("data read:\r\n");
        printf("connection handle: %u\r\n", params->connHandle);
        printf("attribute handle: %u", params->handle);
        if (params->handle == _my_custom_temperature_service->getValueHandle()) {
            printf(" (temperature characteristic)\r\n");
        } else {
            printf("\r\n");
        }
    }

    void on_updates_enabled(GattAttribute::Handle_t handle){
        if (handle == _my_custom_temperature_service->getValueHandle()) {
            printf("update enabled on temperature characteristic\r\n");
        } 
    }

    // void on_updates_disabled(const GattDataSentCallbackParams *params){
    //     printf("update disabled on handle %d\r\n", params->attHandle);
    // }

    void blink() {
        _alive_led = !_alive_led;
    }

private:
    /* Event handler */

    void onConnectionComplete(const ble::ConnectionCompleteEvent&) {
       blinkEventId = _event_queue.call_every(500, this, &MyDemo::blink);
       temperatureEventId = _event_queue.call_every(1000, &_temperatureReader, &TemperatureReader::readTemperature);

    }

    void onDisconnectionComplete(const ble::DisconnectionCompleteEvent&) {
        _event_queue.cancel(blinkEventId);
        _event_queue.cancel(temperatureEventId);
        _ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);
    }

private:
    BLE &_ble;
    events::EventQueue &_event_queue;
    DigitalOut _alive_led;
    DigitalOut _actuated_led;

    Player _player;
    Displayer _displayer;
    TemperatureReader _temperatureReader;

    UUID _my_custom_music_service_uuid;
    UUID _my_custom_lcd_service_uuid;
    UUID _my_custom_temperature_service_uuid;

    MyCustomMusicService *_my_custom_music_service;
    MyCustomLCDService *_my_custom_lcd_service;
    MyCustomTemperatureService *_my_custom_temperature_service;

    uint8_t _adv_buffer[ble::LEGACY_ADVERTISING_MAX_SIZE];
    ble::AdvertisingDataBuilder _adv_data_builder;
};

/** Schedule processing of events from the BLE middleware in the event queue. */
void schedule_ble_events(BLE::OnEventsToProcessCallbackContext *context) {
    event_queue.call(Callback<void()>(&context->ble, &BLE::processEvents));
}

int main()
{
    printf("\nHi!\n");

    BLE &ble = BLE::Instance();
    ble.onEventsToProcess(schedule_ble_events);

    MyDemo demo(ble, event_queue);
    demo.start();

    return 0;
}

