#include <sensor.h>

class SoundSensor : public Sensor {
    public:
        SoundSensor(int trigger, int echo, int threshold, long watch_dog = 100):Sensor(trigger, watch_dog){
            this->trigger = trigger;
            this->echo = echo;
            this->threshold = threshold;
            digitalWrite(this->trigger, LOW);
        };
        bool read();
        long getDistance();
    private:
        uint8_t trigger;
        uint8_t echo;
        int threshold;
        long distance;
};

bool SoundSensor::read(){
    digitalWrite(this->trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigger, LOW);

    long t = pulseIn(this->echo, HIGH);
    this->distance = t / 59;
    
    return this->distance < threshold;
}

long SoundSensor::getDistance(){
    return this->distance;
}
