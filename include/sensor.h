#include <Arduino.h>

class Sensor {
    public:
        Sensor(int input, long watch_dog);
        virtual bool hasChanged();
        virtual bool getStatus();
        virtual bool read();
    protected:
        int input;
        long timer;
        bool status;
        long bounce_wd = 100;
};

Sensor::Sensor(int input, long watch_dog = 100){
    this->input = input;
    this->bounce_wd = watch_dog;
    this->status = false;
}

bool Sensor::hasChanged(){
    bool actual_read = this->read();
    if ((actual_read != this->status) && (millis()-this->timer >= this->bounce_wd)){
        this->timer = millis();
        this->status = actual_read;
        return true;
    }
    return false;
}

bool Sensor::getStatus(){
    return this->status;
}