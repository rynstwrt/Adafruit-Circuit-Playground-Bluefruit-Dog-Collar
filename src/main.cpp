#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <TimerEvent.h>
#include <music.h>


int currentBrightness = MIN_BRIGHTNESS;
int currentMode = 0;
int previousMode = -1;

bool leftButtonState = false;
unsigned long leftButtonTimer = 0;
bool leftButtonActive = false;
bool leftButtonLongPressActive = false;

bool rightButtonState = false;
unsigned long rightButtonTimer = 0;
bool rightButtonActive = false;
bool rightButtonLongPressActive = false;

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


void changeMode(bool increase)
{
    currentMode += increase ? 1 : -1;
    CircuitPlayground.clearPixels();
}


void changeBrightness(bool increase)
{
    currentBrightness += increase ? BRIGHTNESS_INCREMENT : -BRIGHTNESS_INCREMENT;

    if (currentBrightness >= 255)
    {
        currentBrightness = 255;
        CircuitPlayground.redLED(true);
    }
    else if (currentBrightness <= MIN_BRIGHTNESS)
    {
        currentBrightness = MIN_BRIGHTNESS;
        CircuitPlayground.redLED(true);
    }
    else 
    {
        CircuitPlayground.redLED(false);
    }

    CircuitPlayground.setBrightness(currentBrightness);
    delay(BRIGHTNESS_CHANGE_DELAY);
}


void handleButtons(bool isRightButton)
{
    bool currentButtonState = isRightButton ? CircuitPlayground.rightButton() : CircuitPlayground.leftButton();
    bool activeStatus = isRightButton ? rightButtonActive : leftButtonActive;

    if (currentButtonState)
    {
        if (!activeStatus)
        {
            isRightButton ? rightButtonActive = true : leftButtonActive = true;
            isRightButton ? rightButtonTimer = millis() : leftButtonTimer = millis();
        }

        bool longPressActive = isRightButton ? rightButtonLongPressActive : leftButtonLongPressActive;
        unsigned long buttonTimer = isRightButton ? rightButtonTimer : leftButtonTimer;
        if (millis() - buttonTimer > LONG_BUTTON_HOLD_THRESHOLD && !longPressActive) // long hold
        {
            isRightButton ? rightButtonLongPressActive = true : leftButtonLongPressActive = true;
            isRightButton ? rightButtonState = !rightButtonState : leftButtonState = !leftButtonState;
        }
    }
    else 
    {
        if (activeStatus)
        {
            isRightButton ? rightButtonLongPressActive = false : leftButtonLongPressActive = false;

            unsigned long buttonTimer = isRightButton ? rightButtonTimer : leftButtonTimer;
            if (millis() - buttonTimer < LONG_BUTTON_HOLD_THRESHOLD) // short press
            {
                isRightButton ? changeMode(true) : changeMode(false);
            }
        }
        else 
        {
            isRightButton ? rightButtonState = !rightButtonState : leftButtonState = !leftButtonState;
        }

        isRightButton ? rightButtonActive = false : leftButtonActive = false;
    }
}


void playStartupTune()
{
    CircuitPlayground.playTone(getFrequencyFromNote("E", 6), 50);
    CircuitPlayground.playTone(getFrequencyFromNote("E", 6), 50);
    delay(50);
    CircuitPlayground.playTone(getFrequencyFromNote("E", 6), 100);
    delay(50);
    CircuitPlayground.playTone(getFrequencyFromNote("C", 6), 100);
    CircuitPlayground.playTone(getFrequencyFromNote("E", 6), 100);
    CircuitPlayground.playTone(getFrequencyFromNote("G", 6), 100);
    delay(200);
    CircuitPlayground.playTone(getFrequencyFromNote("G", 2), 100);
}


void setup()
{
    CircuitPlayground.begin(currentBrightness);
    CircuitPlayground.redLED(true);

    rainbowSpinEvent.set(2, rainbowSpin);
    rainbowWipeEvent.set(50, rainbowWipe);
    rainbowTheaterEvent.set(100, rainbowTheater);
    rainbowTraceEvent.set(50, rainbowTrace);
    rainbowAngelEvent.set(45, rainbowAngel);
    rainbowSoundReactiveEvent.set(50, rainbowSoundReactive);
    rainbowAngelTraceEvent.set(45, rainbowAngelTrace);
    cancelAllEvents();

    playStartupTune();
}


void loop()
{   
    handleButtons(false);
    handleButtons(true);

    if (leftButtonLongPressActive)
        changeBrightness(false);
    else if (rightButtonLongPressActive)
        changeBrightness(true);
    
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