#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <FastLED.h>

// Animations
#define LED_ON     1
#define LED_OFF    2
#define COLOR_PASS 3

class LEDStrip {
    public:
        // Cosntructor
        LEDStrip(int numberOfLEDs);
        
        // Accessors
        int getNumLED() { return numLED; }
        CRGB* getStrip() { return leds; }

        // Mutators
        void setAnimation(int animation);
        void runAnimation();
    private:
        int numLED;
        int animation;
 
        CRGB* leds;

        void on();
        void off();
        void color_pass();

        void (LEDStrip::*animationFunction)();
};

#endif