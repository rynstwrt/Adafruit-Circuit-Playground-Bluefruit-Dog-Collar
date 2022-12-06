#include <Adafruit_CircuitPlayground.h>
#include <constants.h>


void off()
{
    CircuitPlayground.clearPixels();
    delay(100);
}


void blink(float delayTime)
{
    for (int i = 0; i < NUM_LEDS; ++i)
    {
        CircuitPlayground.setPixelColor(i, 255, 0, 255);
    }
    delay(delayTime);
    CircuitPlayground.clearPixels();
    delay(delayTime);
}


// void rainbow(float delayTime)
// {
//     if (shouldExit())
//         return;
        
//     for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
//     {
//         for (int i = 0; i < NUM_LEDS; ++i)
//         {
//             int pixelHue = firstPixelHue + (i * 65536 / NUM_LEDS);
//             CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(pixelHue));
//             delay(100);
//         }
//         delay(delayTime);
//     }
// }


void rainbow(float delayTime)
{
    for (long pixelHue = 0; pixelHue < 5 * 65536; ++pixelHue)
    {
        int hue = pixelHue + (65536 / NUM_LEDS);
        for (int i = 0; i < NUM_LEDS; ++i)
        {
            CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(hue));
        }

        delay(delayTime);
    }
}


void wipe(float delayTime, int r, int g, int b)
{
    CircuitPlayground.clearPixels();

    for (int i = 0; i < NUM_LEDS; ++i)
    {
        CircuitPlayground.setPixelColor(i, r, g, b);
        delay(delayTime);
    }

    for (int i = 0; i < NUM_LEDS; ++i)
    {
        CircuitPlayground.setPixelColor(i, 0, 0, 0);
        delay(delayTime);
    }
}