#include <math.h>

const int NUM_LEDS = 10;
const int LED_BRIGHTNESS = 20;

const int NUM_MODES = 3;
const float BUTTON_DEBOUNCE = 150;

const int RAINBOW_STEP = floor(255 / NUM_LEDS);