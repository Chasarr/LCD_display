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
    unsigned short nbr = menu.prompt();
    unsigned int tones[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6,
                            NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6};
    for (unsigned short i = 0; i < nbr; i++) {
        tone(BEEP_PIN, tones[i]);
        delay(500);
    }
    for (unsigned short i = 0; i < 10; i++) {
        tone(BEEP_PIN, tones[nbr]);
        delay(200);
    }
}

void loop() {
    delay(500);
}