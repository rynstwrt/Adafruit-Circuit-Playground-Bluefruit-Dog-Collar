#include <Adafruit_CircuitPlayground.h>
#include <constants.h>


int lastLeftButtonState;
int lastRightButtonState;
bool shouldExit()
{
    bool leftState = CircuitPlayground.leftButton();
	bool rightState = CircuitPlayground.rightButton(); 

	if (lastLeftButtonState != leftState)
	{
		lastLeftButtonState = leftState;
		return true;
	}

	if (lastRightButtonState != rightState)
	{
		lastRightButtonState = rightState;
		return true;
	}

    return false;
}


void off()
{
    CircuitPlayground.clearPixels();
    delay(100);
}


void blink(float delayTime)
{
    if (shouldExit())
        return;

    for (int i = 0; i < NUM_LEDS; ++i)
    {
        CircuitPlayground.setPixelColor(i, 255, 0, 255);
    }
    delay(delayTime);
    CircuitPlayground.clearPixels();
    delay(delayTime);
}


void rainbow(float delayTime)
{
    if (shouldExit())
        return;
        
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
    {
        for (int i = 0; i < NUM_LEDS; ++i)
        {
            int pixelHue = firstPixelHue + (i * 65536 / NUM_LEDS);
            CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(pixelHue));
            delay(100);
        }
        delay(delayTime);
    }
}