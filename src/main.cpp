
#include <ESPRandom.h>
#include <cstdlib>
#include "common.hpp"


#ifdef    ARDUINO_ARCH_ESP32

#define SOUND_PWM_CHANNEL   0
#define SOUND_RESOLUTION    8 // 8 bit resolution
#define SOUND_ON            (1<<(SOUND_RESOLUTION-1)) // 50% duty cycle
#define SOUND_OFF           0                         // 0% duty cycle

void tone(int pin, int frequency, int duration) {
    Serial.println(__cplusplus);
    Serial.println("I'm makin sound ovah heah");
    ledcSetup(SOUND_PWM_CHANNEL, frequency, SOUND_RESOLUTION);  // Set up PWM channel
    ledcAttachPin(pin, SOUND_PWM_CHANNEL);                      // Attach channel to pin
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_ON);
    delay(duration);
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_OFF);
    Serial.println("Still makin' sound ovah heah");
}

#endif


boolean debounce(const int &btn);

void drawing();

void benchmark();

using namespace std;


//String GUI::someString = "Hello worldz";
void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BEEP_PIN, OUTPUT);
    pinMode(LEFT_BTN, INPUT_PULLUP);
    pinMode(ENTER_BTN, INPUT_PULLUP);
    pinMode(RIGHT_BTN, INPUT_PULLUP);
    pinMode(ANALOG_X, INPUT);
    pinMode(ANALOG_Y, INPUT);


    PromptBox box1 = PromptBox("Yes or no?");
    //PromptBox box2(promptText2);
    box1.draw();
}

void loop(){
    delay(500);
}
/*

int disp_arr[X_MAX][Y_MAX];

void loop() {
    drawing();
}

*/
/**
 * Compares time taken between fillRect() and my own algorithm using two for-loops
 *//*


void benchmark() {
    unsigned long int time;

    */
/**
     * FIRST
     *
    *//*

    //Clears setup
    display.clearDisplay();
    delay(500);

    time = millis();
    display.fillRect(0, 0, X_MAX, Y_MAX, BLACK);
    display.drawChildren();
    unsigned int firstTime = millis() - time;
    //Print & cleanup
    Serial.print("First method: ");
    Serial.println(firstTime);
    delay(2500);  //Inspection display for errors

    */
/**
     * SECOND
     *
    *//*


    display.clearDisplay();
    delay(500);

    time = millis();

    for (unsigned short int y = 0; y < Y_MAX; y++) {
        for (unsigned short int x = 0; x < X_MAX; x++) {
            display.drawPixel(x, y, BLACK);
        }
    }

    display.drawChildren();
    unsigned int secondTime = millis() - time;
    Serial.print("Second method: ");
    Serial.println(secondTime);
    delay(2500);  //Inspection display for errors

    */
/**
     * PRINTING WINNER
     *
    *//*


    const char *winner = firstTime < secondTime ? "First is fastest" : "Second is fastest";
    display.clearDisplay();
    display.setCursor(0, 0);
    display.write(winner);
    display.refresh();

    //Stops further looping
    for (;;) {
        delay(1000000);
    }
}

void drawing() {
    boolean color = debounce(BTN_PIN);
    unsigned short int radius = 10;

    const unsigned short int xRead = analogRead(ANALOG_X);
    const unsigned short int yRead = analogRead(ANALOG_Y);
    unsigned short int xPos = map(4095 - xRead, 0 + radius, 4095 - radius, 0 + radius, X_MAX - radius);
    unsigned short int yPos = map(yRead, 0 + radius, 4095 - radius, 0 + radius, Y_MAX - radius);
    Serial.print("X: ");
    Serial.print(xPos);
    Serial.print("\tY: ");
    Serial.println(yPos);
    display.fillCircle(xPos, yPos, 10, color);
    display.drawChildren();
}

// Variables will change:
boolean ledState = LOW;    // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = HIGH;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

boolean debounce(const int &btn) {
    // read the state of the switch into a local variable:
    int reading = digitalRead(BTN_PIN);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != buttonState) {
            buttonState = reading;

            // only toggle the LED if the new button state is HIGH
            if (buttonState == HIGH) {
                ledState = !ledState;
            }
        }
    }

    // set the LED:
    digitalWrite(LED_PIN, ledState);

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;
    return !ledState;
}*/
