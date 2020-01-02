#include <Adafruit_NeoPixel.h>

#define CLEAR 0
#define ROTATION 1
#define STATUS 2
#define FILL 3

#define BLACK 0x00000000
#define WHITE 0x00323232

class Light : public Adafruit_NeoPixel {
    public:
        Light(uint16_t numPixels, uint16_t pin):Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800){
            this->state = CLEAR;
        }
        void rotate(uint32_t color, uint16_t period, uint32_t background);
        void clear(uint32_t background);
        void setAll(uint32_t fill);
        void run();
    private:
        void exec_rotate();
        void exec_status();
        int state;
        long rotate_timer;
        uint8_t rotate_index;
        uint32_t rotate_color;
        uint32_t rotate_background;
        uint16_t rotate_period;
};

void Light::rotate(uint32_t color, uint16_t period, uint32_t background = BLACK){
    this->state = ROTATION;
    this->rotate_period = period;
    this->rotate_index = 0;
    this->rotate_color = color;
    this->rotate_background = background;
    this->rotate_timer = millis();
}

void Light::exec_rotate(){
    if(millis()-this->rotate_timer >= this->rotate_period){
        if (this->rotate_index == this->numPixels()) {
            this->rotate_index = 0;
        }
        if(this->rotate_index == 0){
            this->setPixelColor(this->numPixels() - 1, this->rotate_background);
        }
        else {
            this->setPixelColor(this->rotate_index - 1, this->rotate_background);
        }
        this->setPixelColor(this->rotate_index, this->rotate_color);
        this->show();
        this->rotate_timer = millis();
        this->rotate_index++;
    }
}

void Light::exec_status(){}

void Light::clear(uint32_t background=BLACK){
    this->state = CLEAR;
    this->fill(background, 0, this->numPixels());
    this->show();
}

void Light::setAll(uint32_t fill=WHITE){
    this->state = FILL;
    this->fill(fill, 0, this->numPixels());
    this->show();
}

void Light::run(){
    switch (this->state){
    case ROTATION:
        this->exec_rotate();
        break;
    case STATUS:
        this->exec_status();
        break;
    default:
        break;
    }
}
