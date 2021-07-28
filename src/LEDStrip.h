#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#define FASTLED_INTERNAL
#include <FastLED.h>

// Animations
#define LED_ON     1
#define LED_OFF    2
#define COLOR_PASS 3

class LEDStrip {
    public:
        // Cosntructor
        LEDStrip(int numberOfLEDs);
        LEDStrip(int numberofLEDs, int animationType);
        
        // Accessors
        int getNumLED() { return numLED; }
        int getDelay() { return animationDelay; }

        CRGB* getStrip() { return leds; }

        // Mutators
        void setAnimation(int animation);
        void runAnimation();
        void stopAnimation();

        void setDelay(int delay) {animationDelay = delay;}
        void setBrightness(int brightness);
    private:
        int numLED;
        int animation;
        int animationDelay;
        int animationBrightness;
 
        CRGB* leds;

        void on();
        void off();
        void color_pass();

        void (LEDStrip::*animationFunction)();
};

#endif