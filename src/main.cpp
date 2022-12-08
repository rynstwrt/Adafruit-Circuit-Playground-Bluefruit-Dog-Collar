#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <TimerEvent.h>


int currentBrightness = MIN_BRIGHTNESS;
bool hitMaxBrightness = false;
int currentMode = 0;
int previousMode = -1;

TimerEvent rainbowSpinEvent;
TimerEvent solidOrangeEvent;
TimerEvent rainbowEvent;
TimerEvent rainbowWipeEvent;
TimerEvent rainbowTheaterEvent;
TimerEvent rainbowTraceEvent;
TimerEvent rainbowAngelEvent;
TimerEvent rainbowSoundReactiveEvent;


void cancelAllEvents()
{
    rainbowSpinEvent.disable();
    rainbowSpinEvent.reset();

    solidOrangeEvent.disable();
    solidOrangeEvent.reset();

    rainbowEvent.disable();
    rainbowEvent.reset();

    rainbowWipeEvent.disable();
    rainbowWipeEvent.reset();

    rainbowTheaterEvent.disable();
    rainbowTheaterEvent.reset();

    rainbowTraceEvent.disable();
    rainbowTraceEvent.reset();

    rainbowAngelEvent.disable();
    rainbowAngelEvent.reset();

    rainbowSoundReactiveEvent.disable();
    rainbowSoundReactiveEvent.reset();
}


void updateAllEvents()
{
    rainbowSpinEvent.update();
    solidOrangeEvent.update();
    rainbowEvent.update();
    rainbowWipeEvent.update();
    rainbowTheaterEvent.update();
    rainbowTraceEvent.update();
    rainbowAngelEvent.update();
    rainbowSoundReactiveEvent.update();
}


void setup()
{
    CircuitPlayground.begin(currentBrightness);

    rainbowSpinEvent.set(2, rainbowSpin);
    solidOrangeEvent.set(100, solidOrange);
    rainbowEvent.set(2, rainbow);
    rainbowWipeEvent.set(50, rainbowWipe);
    rainbowTheaterEvent.set(100, rainbowTheater);
    rainbowTraceEvent.set(50, rainbowTrace);
    rainbowAngelEvent.set(35, rainbowAngel);
    rainbowSoundReactiveEvent.set(50, rainbowSoundReactive);

    cancelAllEvents();
}


void loop()
{   
    if (CircuitPlayground.leftButton())
	{
		currentBrightness += BRIGHTNESS_INCREMENT;

        if (!hitMaxBrightness && currentBrightness >= 255)
        {
            hitMaxBrightness = true;
            currentBrightness = 255;
            CircuitPlayground.redLED(true);
        }
        else if (hitMaxBrightness)
        {
            currentBrightness = MIN_BRIGHTNESS;
            hitMaxBrightness = false;
            CircuitPlayground.redLED(false);
        }

        CircuitPlayground.setBrightness(currentBrightness);
        delay(BUTTON_DEBOUNCE);
	}
	
    if (CircuitPlayground.rightButton())
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
                solidOrangeEvent.enable();
            else if (currentMode == 2)
                rainbowEvent.enable();
            else if (currentMode == 3)
                rainbowWipeEvent.enable();
            else if (currentMode == 4)
                rainbowTheaterEvent.enable();
            else if (currentMode == 5)
                rainbowTraceEvent.enable();
            else if (currentMode == 6)
                rainbowAngelEvent.enable();
            else if (currentMode == 7)
                rainbowSoundReactiveEvent.enable();

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