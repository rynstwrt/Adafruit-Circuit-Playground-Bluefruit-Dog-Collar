#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <TimerEvent.h>


int currentMode = 0;
int previousMode = -1;

TimerEvent rainbowSpinEvent;
TimerEvent rainbowEvent;
TimerEvent rainbowWipeEvent;
TimerEvent rainbowTheaterEvent;
TimerEvent rainbowTraceEvent;
TimerEvent orangeBlackWipeEvent;


void cancelAllEvents()
{
    rainbowSpinEvent.disable();
    rainbowSpinEvent.reset();

    rainbowEvent.disable();
    rainbowEvent.reset();

    rainbowWipeEvent.disable();
    rainbowWipeEvent.reset();

    rainbowTheaterEvent.disable();
    rainbowTheaterEvent.reset();

    rainbowTraceEvent.disable();
    rainbowTraceEvent.reset();

    orangeBlackWipeEvent.disable();
    orangeBlackWipeEvent.reset();
}


void updateAllEvents()
{
    rainbowSpinEvent.update();
    rainbowEvent.update();
    rainbowWipeEvent.update();
    rainbowTheaterEvent.update();
    rainbowTraceEvent.update();
    orangeBlackWipeEvent.update();
}


void setup()
{
    CircuitPlayground.begin(LED_BRIGHTNESS);

    rainbowSpinEvent.set(2, rainbowSpin);
    rainbowEvent.set(2, rainbow);
    rainbowWipeEvent.set(50, rainbowWipe);
    rainbowTheaterEvent.set(100, rainbowTheater);
    rainbowTraceEvent.set(50, rainbowTrace);
    orangeBlackWipeEvent.set(50, orangeBlackWipe);

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
                rainbowSpinEvent.enable();
            else if (currentMode == 1)
                rainbowEvent.enable();
            else if (currentMode == 2)
                rainbowWipeEvent.enable();
            else if (currentMode == 3)
                rainbowTheaterEvent.enable();
            else if (currentMode == 4)
                rainbowTraceEvent.enable();
            else if (currentMode == 5)
                orangeBlackWipeEvent.enable();

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