#include "LEDStrip.h"

// Constructor
LEDStrip::LEDStrip(int numberOfLEDs) {
    numLED = numberOfLEDs;
    animationDelay = 25;
    animationBrightness = 10;

    leds = new CRGB[numberOfLEDs];
    FastLED.setBrightness(animationBrightness);

    setAnimation(2);
}

LEDStrip::LEDStrip(int numberOfLEDs, int animationType) {
    numLED = numberOfLEDs;
    animationDelay = 25;
    animationBrightness = 10;

    leds = new CRGB[numberOfLEDs];
    FastLED.setBrightness(animationBrightness);

    setAnimation(animationType);
}

void LEDStrip::setBrightness(int brightness) {
    this->animationBrightness = brightness;
    FastLED.setBrightness(brightness);
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

void LEDStrip::stopAnimation() {
    animationFunction = &LEDStrip::off;

    runAnimation();
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
    }

    for (int i = numLED - 1; i >= 0; i--) {
        leds[i] = CRGB(0, 100, 0);

        FastLED.show();
    }

    for (int i = 0; i < numLED; i++) {
        leds[i] = CRGB(0, 0, 100);

        FastLED.show();
    }

    for (int i = numLED - 1; i >= 0; i--) {
        leds[i] = CRGB(100, 0, 100);

        FastLED.show();
    }
}