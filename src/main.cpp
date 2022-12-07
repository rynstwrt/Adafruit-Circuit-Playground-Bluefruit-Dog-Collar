#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <TimerEvent.h>


int currentMode = 0;
int previousMode = -1;
TimerEvent blinkEvent;
TimerEvent rainbowSpinEvent;
TimerEvent rainbowEvent;
TimerEvent rainbowWipeEvent;


void cancelAllEvents()
{
    blinkEvent.disable();
    blinkEvent.reset();

    rainbowSpinEvent.disable();
    rainbowSpinEvent.reset();

    rainbowEvent.disable();
    rainbowEvent.reset();

    rainbowWipeEvent.disable();
    rainbowWipeEvent.reset();
}


void updateAllEvents()
{
    blinkEvent.update();
    rainbowSpinEvent.update();
    rainbowEvent.update();
    rainbowWipeEvent.update();
}


void setup()
{
    CircuitPlayground.begin(LED_BRIGHTNESS);

    blinkEvent.set(500, blink);
    rainbowSpinEvent.set(10, rainbowSpin);
    rainbowEvent.set(5, rainbow);
    rainbowWipeEvent.set(20, rainbowWipe);

    cancelAllEvents();
}


void loop()
{   
    if (CircuitPlayground.leftButton())
	{
		currentMode -= 1;
        CircuitPlayground.clearPixels();
        delay(BUTTON_DEBOUNCE);
	}
	else if (CircuitPlayground.rightButton())
	{
		currentMode += 1;
        CircuitPlayground.clearPixels();
		delay(BUTTON_DEBOUNCE);
	}

    if (currentMode == NUM_MODES)
        currentMode = 0;
    else if (currentMode < 0)
        currentMode = NUM_MODES - 1;

    if (CircuitPlayground.slideSwitch())
    {
        if (currentMode != previousMode)
        {
            cancelAllEvents();

            if (currentMode == 0)
                blinkEvent.enable();
            else if (currentMode == 1)
                rainbowSpinEvent.enable();
            else if (currentMode == 2)
                rainbowEvent.enable();
            else if (currentMode == 3)
                rainbowWipeEvent.enable();

            previousMode = currentMode;
        }
    }
    else
    {
        cancelAllEvents();
        CircuitPlayground.clearPixels();
        previousMode = -1;
    }

    updateAllEvents();
}