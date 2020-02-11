#include <sensor.h>

class SoundSensor : public Sensor {
    public:
        SoundSensor(int trigger, 
                    int echo, 
                    int threshold_min, 
                    int threshold_max, 
                    long distance_factor, 
                    long watch_dog
                    ):Sensor(trigger, watch_dog){
            this->trigger = trigger;
            this->echo = echo;
            this->threshold_min = threshold_min;
            this->threshold_max = threshold_max;
            this->distance_factor = distance_factor;
            digitalWrite(this->trigger, LOW);
        };
        bool read();
        long getDistance();
    private:
        uint8_t trigger;
        uint8_t echo;
        int threshold_min;
        int threshold_max;
        long distance;
        float distance_factor;
};

bool SoundSensor::read(){
    digitalWrite(this->trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(this->trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigger, LOW);

    long t = pulseIn(this->echo, HIGH);

    this->distance = t / this->distance_factor;

    return ((this->distance >= this->threshold_min) && (this->distance <= threshold_max));
}

long SoundSensor::getDistance(){
    return this->distance;
}
