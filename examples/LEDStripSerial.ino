#define FASTLED_INTERNAL
#include <FastLED.h>
#include "LEDStrip.h"

#define CMDBUFFSIZE 16

LEDStrip strip(150);
char cmdBuffer[CMDBUFFSIZE];

void setup() 
{
  FastLED.addLeds<WS2812, 2, GRB>(strip.getStrip(), 150);
  strip.setAnimation(LED_OFF);

  Serial.begin(9600);

  Serial.println("Welcome to LEDStrip!");
  Serial.println("A=[animation code]\t1 = ON, 2 = OFF, 3 = Color Pass");
}
 
void loop() {
  if (Serial.available()) {
    int charsRead = Serial.readBytesUntil('\n', cmdBuffer, sizeof(cmdBuffer) - 1);
    cmdBuffer[charsRead] = '\0';

    Serial.print("> "); Serial.println(cmdBuffer);

    if (strlen(cmdBuffer) < 3 || cmdBuffer[1] != '=') Serial.println("Invalid command.");
    else {
      switch(toupper(cmdBuffer[0])) {
        case 'A':
          strip.setAnimation(atoi(&cmdBuffer[2]));
          Serial.println("Animation set.");
          break;
        default:
          Serial.println("Invalid command.");
      }
    }
  }

  strip.runAnimation();
}