#include <Arduino.h>


const int NUM_LEDS = 10;
const int NUM_MODES = 7;
const float BUTTON_DEBOUNCE = 200;

const int RAINBOW_STEP = floor(255 / NUM_LEDS);

const int MAX_DB_THRESHOLD = 100;

const int MIN_BRIGHTNESS = 30;
const int BRIGHTNESS_INCREMENT = 50;

const int BLUETOOTH_PACKET_TIMEOUT = 10;

const String MUSIC_NOTES[13] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A"};
const int MUSIC_NOTE_DURATION = 100;