/************************************
 Project that uses a Sharp monochrome LCD display together with my self made graphics library
 ***********************************/
#include <ESPRandom.h>
#include <cstdlib>
#include "common.hpp"
using namespace std;

/**
 * Setup function
 */
void setup() {
    Serial.begin(115200);       //Initializes serial communication if computer is connected
    //Initializes pins
    pinMode(LED_PIN, OUTPUT);
    pinMode(BEEP_PIN, OUTPUT);
    pinMode(LEFT_BTN, INPUT_PULLUP);
    pinMode(ENTER_BTN, INPUT_PULLUP);
    pinMode(RIGHT_BTN, INPUT_PULLUP);
    pinMode(ANALOG_X, INPUT);
    pinMode(ANALOG_Y, INPUT);

    //Short beep indicating that the device has started
    digitalWrite(LED_PIN, HIGH);
    tone(BEEP_PIN);
    digitalWrite(LED_PIN, LOW);
    MainMenu menu;
    menu.draw();

}

void loop() {
    delay(500);
}