#include <Arduino.h>
#include <settings.h>

#include <sound_sensor.h>
#include <light.h>
#include <llp.h>


#define WAITING_FOR_BOTTLE 1
#define READING_BOTTLE 2
#define WAITING_RESPONSE 3
#define DONE 4

#define PICTURE_THRESHOLD 2000
#define COOLDOWN_THRESHOLD 5000
#define RESPONSE_TIMEOUT 30000

Light pixels = Light(PIXEL::NUM_PIXELS, IO::LED_OUTPUT);
SoundSensor sensor = SoundSensor(IO::TRIGGER, IO::ECHO, 25, 500);

DataPack input = DataPack();

uint8_t remote_command = COM::PASS;
uint8_t remote_value = 0;

uint8_t device_status = WAITING_FOR_BOTTLE;
long device_timer = millis();


void setup(){
    Serial.begin(115200);
    IO::init();
    pixels.begin();
    pixels.clear();
}

void loop(){
    if(input.available(Serial)){
        if(input.hasKey(COM::COMMAND_KEY)) {
            remote_command = input.getData(COM::COMMAND_KEY);
        }
        if(input.hasKey(COM::VALUE_KEY)){
            remote_value = input.getData(COM::VALUE_KEY);
        }
    }

    if(device_status == WAITING_FOR_BOTTLE && (sensor.hasChanged() && sensor.getStatus())) {
        Serial.println(sensor.getDistance());
        pixels.setAll(WHITE);
        device_status = READING_BOTTLE;
        device_timer = millis();
    }

    else if(device_status == READING_BOTTLE) {
        if(sensor.hasChanged() && !sensor.getStatus()) {
            pixels.clear();
            device_status = WAITING_FOR_BOTTLE;
        }
        else if(millis() - device_timer > PICTURE_THRESHOLD){
            device_status = WAITING_RESPONSE;
            device_timer = millis();
            pixels.clear();
            pixels.rotate(0x00320032, PIXEL::PERIOD);
            
            DataPack out = DataPack();
            out.addData(COM::COMMAND_KEY, COM::REQUEST);
            out.write(Serial);
        }
    }

    else if(device_status == WAITING_RESPONSE && (remote_command == COM::RESPONSE || millis() - device_timer > RESPONSE_TIMEOUT)){
        device_status = DONE;
        device_timer = millis();
        if(remote_value == COM::STATUS_OK){
            pixels.setAll(0x00003200);
        }
        else {
            pixels.setAll(0x00320000);
        }
        
    }
    
    else if(device_status == DONE && (millis() - device_timer > COOLDOWN_THRESHOLD)){
        device_status = WAITING_FOR_BOTTLE;
        pixels.clear();
    }
    
    pixels.run();
}
