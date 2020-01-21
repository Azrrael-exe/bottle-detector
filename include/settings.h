/// ---- Version 1.0.2 ----

namespace PIXEL {

    const uint8_t NUM_PIXELS = 16;
    const uint16_t PERIOD = 100;
    
}

namespace IO {
    
    // const uint8_t SENSOR_INPUT = 2;
    const uint8_t LED_OUTPUT = 7;
    const uint8_t TRIGGER = 4;
    const uint8_t ECHO = 5;

    void init(){
        // pinMode(SENSOR_INPUT, INPUT);
        pinMode(LED_OUTPUT, OUTPUT);
        pinMode(TRIGGER, OUTPUT);
        pinMode(ECHO, INPUT);
    }
    
}


namespace COM {

    const uint8_t COMMAND_KEY = 0x0A;
    const uint8_t VALUE_KEY = 0x0B;

    const uint8_t PASS = 0;
    const uint8_t RESPONSE = 1;
    const uint8_t REQUEST = 2;

    const uint16_t STATUS_OK = 200;
    const uint16_t STATUS_FAIL = 400;

}

namespace US {

    const uint8_t THRESHOLD_MIN = 5;
    const uint8_t THRESHOLD_MAX = 25;
    const long DISTANCE_FACTOR = 59;
    const uint8_t WATCHDOG = 100;

}