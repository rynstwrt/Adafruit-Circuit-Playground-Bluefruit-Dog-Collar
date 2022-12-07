#include <Adafruit_CircuitPlayground.h>
#include <constants.h>
#include <led_effects.h>


// void off()
// {
//     CircuitPlayground.clearPixels();
//     delay(100);
// }


// void blink(float delayTime, int r, int g, int b)
// {
//     for (int i = 0; i < NUM_LEDS; ++i)
//     {
//         CircuitPlayground.setPixelColor(i, r, g, b);
//     }
//     delay(delayTime);
//     CircuitPlayground.clearPixels();
//     delay(delayTime);
// }


// // void rainbow(float delayTime)
// // {
// //     for (long pixelHue = 0; pixelHue < 5 * 65536; ++pixelHue)
// //     {
// //         int hue = pixelHue + (65536 / NUM_LEDS);
// //         for (int i = 0; i < NUM_LEDS; ++i)
// //         {
// //             CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(hue));
// //         }

// //         delay(delayTime);
// //     }
// // }


// int rainbowIndex = 0;
// void rainbow()
// {
//     uint32_t color = CircuitPlayground.colorWheel(rainbowIndex);
//     for (int j = 0; j < NUM_LEDS; ++j)
//     {
//         CircuitPlayground.setPixelColor(j, color);
//     }

//     rainbowIndex += 1;
//     rainbowIndex %= 255;
// }


// void wipe(float delayTime, int r, int g, int b)
// {
//     for (int i = 0; i < NUM_LEDS; ++i)
//     {
//         CircuitPlayground.setPixelColor(i, r, g, b);
//         delay(delayTime);
//     }

//     for (int i = 0; i < NUM_LEDS; ++i)
//     {
//         CircuitPlayground.setPixelColor(i, 0, 0, 0);
//         delay(delayTime);
//     }
// }


// void rainbowWipe(float delayTime)
// {
//     for (int i = 0; i < NUM_LEDS; ++i)
//     {
//         CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(i * RAINBOW_STEP));
//         delay(delayTime);
//     }

//     for (int i = 0; i < NUM_LEDS; ++i)
//     {
//         CircuitPlayground.setPixelColor(i, 0, 0, 0);
//         delay(delayTime);
//     }
// }


// void fillTheater(bool offset, uint32_t color)
// {
//     CircuitPlayground.clearPixels();

//     for (int i = 0; i < NUM_LEDS; ++i)
//     {
//         if (i % 2 == 0)
//         {
//             int index = offset ? i + 1 : i;
//             CircuitPlayground.setPixelColor(index, color);
//         }
//     }
// }


// void rainbowTheater(float delayTime)
// {
//     for (int ri = 0; ri < 255; ri++)
//     {
//         uint32_t color = CircuitPlayground.colorWheel(ri);
        
//         fillTheater(false, color);
//         delay(delayTime);
//         fillTheater(true, color);
//         delay(delayTime);
//     }
// }


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