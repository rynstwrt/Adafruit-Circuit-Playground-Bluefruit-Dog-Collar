#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <TimerEvent.h>
#include <music.h>


int currentBrightness = MIN_BRIGHTNESS;
int currentMode = 0;
int previousMode = -1;

unsigned long lastLeftButtonPressTime;
bool leftButtonState = false;
bool leftButtonSinglePress = false;

unsigned long lastRightButtonPressTime;
bool rightButtonState = false;
bool rightButtonSinglePress = false;

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

    if (currentBrightness > 255)
        currentBrightness = 255;
    else if (currentBrightness < MIN_BRIGHTNESS)
        currentBrightness = MIN_BRIGHTNESS;

    CircuitPlayground.setBrightness(currentBrightness);
}


void handleLeftButton()
{
    bool currentLeftButtonState = CircuitPlayground.leftButton();

    if (!currentLeftButtonState && leftButtonState == 0)
    {
        unsigned long currentPressTime = millis();

        if (currentPressTime - lastLeftButtonPressTime < DOUBLE_CLICK_THRESHOLD)
        {
            leftButtonSinglePress = false;
            changeMode(false);
        }
        else 
        {
            leftButtonSinglePress = true;
        }

        lastLeftButtonPressTime = currentPressTime;
        leftButtonState = 1;
    }
    else if (currentLeftButtonState)
    {
        leftButtonState = false;
    }

    if (leftButtonSinglePress == 1 && millis() - lastLeftButtonPressTime > DOUBLE_CLICK_THRESHOLD)
    {
        leftButtonSinglePress = false;
        changeBrightness(false);
    }
}


void handleRightButton()
{
    bool currentRightButtonState = CircuitPlayground.rightButton();

    if (!currentRightButtonState && rightButtonState == 0)
    {
        unsigned long currentPressTime = millis();

        if (currentPressTime - lastRightButtonPressTime < DOUBLE_CLICK_THRESHOLD)
        {
            rightButtonSinglePress = false;
            changeMode(true);
        }
        else 
        {
            rightButtonSinglePress = true;
        }

        lastRightButtonPressTime = currentPressTime;
        rightButtonState = 1;
    }
    else if (currentRightButtonState)
    {
        rightButtonState = false;
    }

    if (rightButtonSinglePress== 1 && millis() - lastRightButtonPressTime > DOUBLE_CLICK_THRESHOLD)
    {
        rightButtonSinglePress = false;
        changeBrightness(true);
    }
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

    lastLeftButtonPressTime = millis();
}


void loop()
{   
    handleLeftButton();
    handleRightButton();
    
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