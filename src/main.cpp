#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <map>


int lastLeftState;
int lastRightState;
int currentMode = 0;


void setup()
{
	CircuitPlayground.begin();
	CircuitPlayground.setBrightness(LED_BRIGHTNESS);
}


void loop()
{
	// rainbow(0.01);
	// wipe(100, 255, 0, 255);

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

	if (currentMode == 0)
	{
		CircuitPlayground.clearPixels();
	}
	else if (currentMode == 1) // rainbow
	{
		rainbow(0.01);
	}
	else if (currentMode == 2)
	{
		blink(0.05);
	}
}