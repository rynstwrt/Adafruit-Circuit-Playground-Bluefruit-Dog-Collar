#include <Adafruit_CircuitPlayground.h>
#include <constants.h>


// ----------- HELPER FUNCTIONS ----------- //
void fillLEDs(uint32_t color)
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        CircuitPlayground.setPixelColor(i, color);
    }
}


// ----------- EFFECTS ----------- //
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


int rainbowIndex = 0;
void rainbow()
{
    uint32_t color = CircuitPlayground.colorWheel(rainbowIndex);
    fillLEDs(color);
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
        CircuitPlayground.setPixelColor(rainbowWipeIndex, (0, 0, 0));
        

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
void rainbowTrace()
{
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(rainbowTraceIndex, CircuitPlayground.colorWheel(rainbowTraceIndex * RAINBOW_STEP));
    ++rainbowTraceIndex;
    rainbowTraceIndex %= NUM_LEDS;
}


bool orangeBlackWipeIsOrange = true;
int orangeBlackWipeIndex = 0;
void orangeBlackWipe()
{
    if (orangeBlackWipeIsOrange)
        CircuitPlayground.setPixelColor(orangeBlackWipeIndex, 255, 84, 10);
    else
        CircuitPlayground.setPixelColor(orangeBlackWipeIndex, 0, 0, 0);

    ++orangeBlackWipeIndex;
    
    if (orangeBlackWipeIndex == NUM_LEDS)
    {
        orangeBlackWipeIsOrange = !orangeBlackWipeIsOrange;
        orangeBlackWipeIndex = 0;
    }
}


