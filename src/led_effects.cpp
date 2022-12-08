#include <Adafruit_CircuitPlayground.h>
#include <constants.h>


int rainbowSpinIndex = 0;
void rainbowSpin()
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(rainbowSpinIndex + i * RAINBOW_STEP));
    }

    ++rainbowSpinIndex;
    rainbowSpinIndex %= 255;
}


void solidOrange()
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        CircuitPlayground.setPixelColor(i, 255, 84, 10);
    }
}


int rainbowIndex = 0;
void rainbow()
{
    uint32_t color = CircuitPlayground.colorWheel(rainbowIndex);
    
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        CircuitPlayground.setPixelColor(i, color);
    }

    ++rainbowIndex;
    rainbowIndex %= 255;
}


bool rainbowWipeFilling = true;
int rainbowWipeIndex = 0;
void rainbowWipe()
{
    if (rainbowWipeFilling)
        CircuitPlayground.setPixelColor(rainbowWipeIndex, CircuitPlayground.colorWheel(rainbowWipeIndex * RAINBOW_STEP));
    else
        CircuitPlayground.setPixelColor(rainbowWipeIndex, 0, 0, 0);
        

    if (rainbowWipeIndex == NUM_LEDS - 1)
    {
        rainbowWipeIndex = -1;
        rainbowWipeFilling = !rainbowWipeFilling;
    }

    ++rainbowWipeIndex;
}


bool theaterOffset = false;
void rainbowTheater()
{
    CircuitPlayground.clearPixels();
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        if (i % 2 == 0)
        {
            int index = (theaterOffset) ? i + 1 : i;
            CircuitPlayground.setPixelColor(index, CircuitPlayground.colorWheel(index * RAINBOW_STEP));
        }
    }
    theaterOffset = !theaterOffset;
}


int rainbowTraceIndex = 0;
bool rainbowTraceForwards = true;
void rainbowTrace()
{
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(rainbowTraceIndex, CircuitPlayground.colorWheel(rainbowTraceIndex * RAINBOW_STEP));

    rainbowTraceIndex += rainbowTraceForwards ? 1 : -1;
    
    if (rainbowTraceIndex == NUM_LEDS || rainbowTraceIndex < 0)
    {
        rainbowTraceForwards = !rainbowTraceForwards;
    }
}


bool rainbowAngelIsOrange = true;
int rainbowAngelIndex = 0;
void rainbowAngel()
{
    if (rainbowAngelIsOrange)
    {
        uint32_t color = CircuitPlayground.colorWheel(RAINBOW_STEP * rainbowAngelIndex * 2);
        CircuitPlayground.setPixelColor(rainbowAngelIndex, color);
        CircuitPlayground.setPixelColor(NUM_LEDS - rainbowAngelIndex - 1, color);
    }
    else
    {
        CircuitPlayground.setPixelColor(rainbowAngelIndex, 0, 0, 0);
        CircuitPlayground.setPixelColor(NUM_LEDS - rainbowAngelIndex - 1, 0, 0, 0);
    }

    ++rainbowAngelIndex;

    if (rainbowAngelIndex == floor(NUM_LEDS / 2))
    {
        rainbowAngelIsOrange = !rainbowAngelIsOrange;
        rainbowAngelIndex = 0;
    }
}


void rainbowSoundReactive()
{
    CircuitPlayground.clearPixels();

    float micPressureLevel = CircuitPlayground.mic.soundPressureLevel(10) - (MAX_DB_THRESHOLD / 10 * 5);
    int numUsedLEDs = floor(micPressureLevel / (MAX_DB_THRESHOLD / 10));

    for (int i = 0; i < numUsedLEDs; ++i)
    {
        CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(i * RAINBOW_STEP));
    }
}