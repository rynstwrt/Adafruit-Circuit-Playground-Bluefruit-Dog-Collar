#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
#include <constants.h>
#include <led_effects.h>
#include <map>


int currentMode = 0;


void setup()
{
	CircuitPlayground.begin();
	CircuitPlayground.setBrightness(LED_BRIGHTNESS);
}


void loop()
{
	if (CircuitPlayground.leftButton())
	{
		currentMode -= 1;
		delay(BUTTON_DEBOUNCE);
	}
	else if (CircuitPlayground.rightButton())
	{
		currentMode += 1;
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
    else if (currentMode == 1)
    {
        rainbowSpin();
    }
    else if (currentMode == 2)
    {
        rainbow();
    }
}