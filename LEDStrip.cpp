#include "LEDStrip.h"

// Constructor
LEDStrip::LEDStrip(int numberOfLEDs) {
    numLED = numberOfLEDs;

    leds = new CRGB[numberOfLEDs];
    animationFunction = &LEDStrip::off;
}

void LEDStrip::setAnimation(int animation) {
    switch (animation) {
        case LED_ON:
            animationFunction = &LEDStrip::on;
            break;
        case LED_OFF:
            animationFunction = &LEDStrip::off;
            break;
        case COLOR_PASS:
            animationFunction = &LEDStrip::color_pass;
            break;
        default:
            animationFunction = &LEDStrip::off;
    }
}

void LEDStrip::runAnimation() {
    (this->*animationFunction)();
}

void LEDStrip::on() {
    for (int i = 0; i < numLED; i++) {
        leds[i] = CRGB(100, 100, 100);
    }

    FastLED.show();
}

void LEDStrip::off() {
    for (int i = 0; i < numLED; i++) {
        leds[i] = CRGB(0, 0, 0);
    }

    FastLED.show();
}

void LEDStrip::color_pass() {
    for (int i = 0; i < numLED; i++) {
        leds[i] = CRGB(100, 0, 0);

        FastLED.show();
        delay(25);
    }

    for (int i = numLED - 1; i >= 0; i--) {
        leds[i] = CRGB(0, 100, 0);

        FastLED.show();
        delay(25);
    }

    for (int i = 0; i < numLED; i++) {
        leds[i] = CRGB(0, 0, 100);

        FastLED.show();
        delay(25);
    }

    for (int i = numLED - 1; i >= 0; i--) {
        leds[i] = CRGB(100, 0, 100);

        FastLED.show();
        delay(25);
    }
}