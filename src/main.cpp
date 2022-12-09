#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <TimerEvent.h>
#include <bluefruit.h>


int currentBrightness = MIN_BRIGHTNESS;
bool hitMaxBrightness = false;
int currentMode = 0;
int previousMode = -1;
bool justTapped = false;

TimerEvent rainbowSpinEvent;
TimerEvent rainbowWipeEvent;
TimerEvent rainbowTheaterEvent;
TimerEvent rainbowTraceEvent;
TimerEvent rainbowAngelEvent;
TimerEvent rainbowSoundReactiveEvent;
TimerEvent rainbowAngelTraceEvent;


void cancelAllEvents()
{
    rainbowSpinEvent.disable();
    rainbowSpinEvent.reset();

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

    rainbowAngelTraceEvent.disable();
    rainbowAngelTraceEvent.reset();
}


void updateAllEvents()
{
    rainbowSpinEvent.update();
    rainbowWipeEvent.update();
    rainbowTheaterEvent.update();
    rainbowTraceEvent.update();
    rainbowAngelEvent.update();
    rainbowSoundReactiveEvent.update();
    rainbowAngelTraceEvent.update();
}


void onLeftButtonClick()
{
    currentMode -= 1;
    CircuitPlayground.clearPixels();  
    delay(BUTTON_DEBOUNCE);
}


void onRightButtonClick()
{
    currentMode += 1;
    CircuitPlayground.clearPixels();
    delay(BUTTON_DEBOUNCE);
}


void onBrightnessButtonTap()
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


void setup()
{
    CircuitPlayground.begin(currentBrightness);

    rainbowSpinEvent.set(2, rainbowSpin);
    rainbowWipeEvent.set(50, rainbowWipe);
    rainbowTheaterEvent.set(100, rainbowTheater);
    rainbowTraceEvent.set(50, rainbowTrace);
    rainbowAngelEvent.set(45, rainbowAngel);
    rainbowSoundReactiveEvent.set(50, rainbowSoundReactive);
    rainbowAngelTraceEvent.set(45, rainbowAngelTrace);

    cancelAllEvents();
}


void loop()
{   
    if (CircuitPlayground.leftButton())
        onLeftButtonClick();
    if (CircuitPlayground.rightButton())
        onRightButtonClick();
    if (CircuitPlayground.readCap(BRIGHTNESS_BUTTON) > BRIGHTNESS_BUTTON_THRESHOLD)
        onBrightnessButtonTap();
    
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
                rainbowWipeEvent.enable();
            else if (currentMode == 2)
                rainbowTheaterEvent.enable();
            else if (currentMode == 3)
                rainbowTraceEvent.enable();
            else if (currentMode == 4)
                rainbowAngelEvent.enable();
            else if (currentMode == 5)
                rainbowSoundReactiveEvent.enable();
            else if (currentMode == 6)
                rainbowAngelTraceEvent.enable();

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