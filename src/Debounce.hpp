#pragma once
#define HIGH 1
#define LOW 0

#define DEBOUNCE_THRESHOLD 20       //How quick can a button click be to be registered?


/**
 * Use this class to input button clicks asynchronously
 * This class takes debouncing into account. There can't be too much code between each update() function call
 */
class Debounce {
public:
    /**
     * Initializes button
     * @param btn Which pin is the button on?
     * @param inverted  Some buttons are pulled up, some are pulled down. Use true or false to fit your needs
     */
    Debounce(unsigned short int btn, bool inverted = true);
    /**
     * Call this function multiple times untill the button returns true or false
     * @return True of the button has been clicked long enough
     */
    bool update();
private:
    bool inverted;
    unsigned short int btn;

    unsigned int lastButtonState;
    unsigned long int lastPressedTime;
    bool pressState;
    bool alreadyPressed;     //Has the pressed button already returned true once?
};