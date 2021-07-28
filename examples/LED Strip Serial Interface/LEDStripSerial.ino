#define FASTLED_INTERNAL
#include <FastLED.h>
#include "LEDStrip.h"

// #define CMDBUFFSIZE 16

LEDStrip strip(150, 1);
// char cmdBuffer[CMDBUFFSIZE];

const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;

void setup() 
{
	FastLED.addLeds<WS2812, 2, GRB>(strip.getStrip(), 150);
  
	Serial.begin(9600);
	Serial.println("Welcome to LEDStrip!");
}
 
void loop() {
	receiveData();
	
	if (newData == true) {
		Serial.print("> "); Serial.println(receivedChars);
		newData = false;

		if (strlen(receivedChars) < 3 || receivedChars[1] != '=') Serial.println("\nInvalid command.\n");
		else {
			int params = atoi(&receivedChars[2]);

			switch(toupper(receivedChars[0])) {
				case 'A':
					strip.setAnimation(params);
					Serial.println("\nAnimation set.\n");
					break;
				case 'B':
					strip.setBrightness(params);
					Serial.println("\nBrightness set.\n");
					break;
				default:
					Serial.println("\nInvalid command.\n");
			}
		}
	}
	
	strip.runAnimation();
}

void receiveData() {
	static boolean inProgress = false;
	static byte ndx = 0;

	char startMarker = '{';
	char endMarker = '}';

	char rc;

	while (Serial.available() > 0 && newData == false) {
		rc = Serial.read();

		if (inProgress == true) {
			if (rc != endMarker) {
				receivedChars[ndx] = rc;
				ndx++;

				if (ndx >= numChars) {
					ndx = numChars - 1;
				}
			} else {
				receivedChars[ndx] = '\0';
				inProgress = false;
				ndx = 0;
				newData = true;
			}
		} else if (rc == startMarker) {
			inProgress = true;
		}
	}
}