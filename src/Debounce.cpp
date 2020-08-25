#include "Debounce.hpp"
#include <Arduino.h>

Debounce::Debounce(unsigned short int btn, bool inverted) {
    this->inverted = inverted;
    this->btn = btn;
    lastButtonState = HIGH;
    lastPressedTime = 0;
    pressState = false;
    alreadyPressed = false;
}

/**
 * Makes sure that a button press doesn't spam inputs
 * @param btnState input 1/HIGH if button is pressed, 0/LOW if button is released
 * @return true if pressed, false if not pressed
 */
bool Debounce::update() {
    unsigned short int btnState = inverted ? !digitalRead(btn) : digitalRead(btn);
    //If the button is pressed the first time the time is stored in 'lastPressedTime' variable
    //'pressState' is set to true, which prevents the time from being measured again
    if (btnState == HIGH && !pressState && !alreadyPressed) {
        lastPressedTime = millis();     //millis() returns system timer
        pressState = true;
        return false;
    }
        //If the button keeps being pressed after initial press
    else if (btnState == HIGH && pressState && !alreadyPressed) {
        //Has the code been executed for long enough? Then the code is executed
        if ((millis() - lastPressedTime) > DEBOUNCE_THRESHOLD) {
            alreadyPressed = true;      //Prevents the function to return true until the button is released
            return true;
        } else {
            return false;
        }
    }
        //When the button gets released this code excecutes and resets everything
    else if (btnState == LOW) {
        pressState = false;
        alreadyPressed = false;
    }
    pressState = false;
    return false;
}