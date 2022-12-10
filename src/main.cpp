#include <Adafruit_CircuitPlayground.h>
#include <led_effects.h>
#include <constants.h>
#include <TimerEvent.h>
#include <bluefruit.h>
#include <packetParser.h>
#include <music.h>


int currentBrightness = MIN_BRIGHTNESS;
bool hitMaxBrightness = false;
bool hitMinBrightness = true;
int currentMode = 0;
int previousMode = -1;

BLEDis bledis; // device info
BLEUart bleuart; // uart over ble
BLEBas blebas; // battery
extern uint8_t packetbuffer[];

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


void onLeftButtonClick()
{
    currentMode -= 1;
    CircuitPlayground.clearPixels();  
    delay(BUTTON_DEBOUNCE);
}


void onRightButtonClick()
{
    currentMode += 1;
    CircuitPlayground.clearPixels();
    delay(BUTTON_DEBOUNCE);
}


void changeBrightness(bool increase)
{
    currentBrightness += increase ? BRIGHTNESS_INCREMENT : -BRIGHTNESS_INCREMENT;

    if (currentBrightness > 255)
        currentBrightness = 255;
    else if (currentBrightness < MIN_BRIGHTNESS)
        currentBrightness = MIN_BRIGHTNESS;

    CircuitPlayground.setBrightness(currentBrightness);

    delay(BUTTON_DEBOUNCE);
}


void setup()
{
    CircuitPlayground.begin(currentBrightness);

    Bluefruit.begin();
    Bluefruit.setTxPower(4);
    Bluefruit.setName("ACPB Dog Collar");

    bledis.setManufacturer("Adafruit Industries");
    bledis.setModel("Circuit Playground Bluefruit");
    bledis.begin();
    
    bleuart.begin();

    blebas.begin();
    blebas.write(100);

    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();
    Bluefruit.Advertising.addService(bleuart);
    Bluefruit.ScanResponse.addName();
    Bluefruit.autoConnLed(false);
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);
    Bluefruit.Advertising.setFastTimeout(30);
    Bluefruit.Advertising.start(0);

    rainbowSpinEvent.set(2, rainbowSpin);
    rainbowWipeEvent.set(50, rainbowWipe);
    rainbowTheaterEvent.set(100, rainbowTheater);
    rainbowTraceEvent.set(50, rainbowTrace);
    rainbowAngelEvent.set(45, rainbowAngel);
    rainbowSoundReactiveEvent.set(50, rainbowSoundReactive);
    rainbowAngelTraceEvent.set(45, rainbowAngelTrace);

    cancelAllEvents();
}


void loop()
{   
    if (CircuitPlayground.leftButton())
        changeBrightness(false);
    if (CircuitPlayground.rightButton())
        changeBrightness(true);

    uint8_t packetLen = readPacket(&bleuart, BLUETOOTH_PACKET_TIMEOUT);
    if (packetLen > 0 && packetbuffer[1] == 'B')
    {
        uint8_t buttonNum = packetbuffer[2] - '0';
        bool pressed = packetbuffer[3] - '0';
        
        if (pressed)
        {
            if (buttonNum == 8) // right
                onRightButtonClick();
            else if (buttonNum == 7) // left
                onLeftButtonClick();
            else if (buttonNum == 5) // up
                changeBrightness(true);
            else if (buttonNum == 6) // down
                changeBrightness(false);
        }
    }
    
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