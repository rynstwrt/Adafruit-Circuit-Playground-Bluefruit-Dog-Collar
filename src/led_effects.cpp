#include <Adafruit_CircuitPlayground.h>
#include <constants.h>


void fillLEDs(uint32_t color)
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        CircuitPlayground.setPixelColor(i, color);
    }
}


bool blinkOff = false;
void blink()
{
    blinkOff = !blinkOff;
    Serial.println("BLINKING");

    if (blinkOff)
    {
        fillLEDs((0, 0, 0));
    }
    else
    {
        fillLEDs((255, 0, 255));
    }
}


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
