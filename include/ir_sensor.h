#include <sensor.h>

class IRSensor : public Sensor {
    public:
        IRSensor(int input, long watch_dog = 100):Sensor(input, watch_dog){};
        bool read();
    private:
};

bool IRSensor::read(){
    return !digitalRead(this->input);
}

