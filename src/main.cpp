#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <TimerEvent.h>
#include <vector>


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

std::vector<TimerEvent*> timerEvents;


void cancelAllEvents()
{
    for (int i = 0; i < NUM_MODES; ++i)
    {
        TimerEvent* event = timerEvents.at(i);
        event->disable();
        event->reset();
    }
}


void updateAllEvents()
{
    for (int i = 0; i < NUM_MODES; ++i)
    {
        TimerEvent* event = timerEvents.at(i);
        event->update();
    }
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


void setup()
{
    CircuitPlayground.begin(currentBrightness);
    CircuitPlayground.redLED(true);

    rainbowSpinEvent.set(2, rainbowSpin);
    timerEvents.push_back(&rainbowSpinEvent);

    rainbowWipeEvent.set(50, rainbowWipe);
    timerEvents.push_back(&rainbowWipeEvent);

    rainbowTheaterEvent.set(100, rainbowTheater);
    timerEvents.push_back(&rainbowTheaterEvent);

    rainbowTraceEvent.set(50, rainbowTrace);
    timerEvents.push_back(&rainbowTraceEvent);

    rainbowAngelEvent.set(45, rainbowAngel);
    timerEvents.push_back(&rainbowAngelEvent);

    rainbowSoundReactiveEvent.set(50, rainbowSoundReactive);
    timerEvents.push_back(&rainbowSoundReactiveEvent);

    rainbowAngelTraceEvent.set(45, rainbowAngelTrace);
    timerEvents.push_back(&rainbowAngelTraceEvent);

    cancelAllEvents();
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

            TimerEvent* event = timerEvents.at(currentMode);
            event->enable();

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