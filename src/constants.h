#include <Arduino.h>


const int NUM_LEDS = 10;
const int NUM_MODES = 7;

const int LONG_BUTTON_HOLD_THRESHOLD = 500;

const int RAINBOW_STEP = floor(255 / NUM_LEDS);

const int MAX_DB_THRESHOLD = 100;

const int MIN_BRIGHTNESS = 15;
const int BRIGHTNESS_CHANGE_DELAY = 25;
const int BRIGHTNESS_INCREMENT = 5;