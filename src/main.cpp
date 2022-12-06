#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <map>


int lastLeftState;
int lastRightState;
int currentMode = 0;


bool shouldStopEffect()
{
    return false;
}


void setup()
{
	CircuitPlayground.begin();
	CircuitPlayground.setBrightness(LED_BRIGHTNESS);
}


void loop()
{
	bool leftState = CircuitPlayground.leftButton();
	bool rightState = CircuitPlayground.rightButton(); 

	if (lastLeftState != leftState)
	{
		currentMode -= 1;
		lastLeftState = leftState;
		delay(BUTTON_DEBOUNCE);
	}

	if (lastRightState != rightState)
	{
		currentMode += 1;
		lastRightState = rightState;
		delay(BUTTON_DEBOUNCE);
	}

	if (currentMode == NUM_MODES)
		currentMode = 0;
	else if (currentMode < 0)
		currentMode = NUM_MODES - 1;

	CircuitPlayground.clearPixels();
	if (currentMode == 1) // rainbow
	{
		rainbow(100);
	}
	else if (currentMode == 2)
	{
		for (int i = 0; i < NUM_LEDS; ++i)
		{
			CircuitPlayground.setPixelColor(i, 255, 0, 255);
		}
	}
}