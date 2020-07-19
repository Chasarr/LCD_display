#include <utility>

#include "common.hpp"
#include "graphics.hpp"

GUI::GUI() {
    initializeGraphics();
}

boolean GUI::firstRun = true;
Adafruit_SharpMem GUI::display = Adafruit_SharpMem(SHARP_SCK, SHARP_MOSI, SHARP_SS, 400, 240);
void GUI::initializeGraphics() {
    Serial.println("Initializing...");
    if (firstRun) {
        Serial.println("Yep it initialized");
        display.begin();
        display.clearDisplay();
        Serial.println("Display is cleared");
        display.write("Yep it initialized");
        display.fillScreen(BLACK);
        display.refresh();
        delay(1000);
        display.clearDisplay();
        display.refresh();

    } else {
        Serial.println("NOPE NOT INITIALIZING TODAY");
        //display.clearDisplay();

        //display.write("NOPE NOT INITIALIZING TODAY");
        delay(1000);
        //display.clearDisplay();

        //display.refresh();

    }
}

PromptBox::PromptBox(String &promptStr) : GUI() {
    this->promptStr = promptStr;

}

void PromptBox::draw(const unsigned short &x, const unsigned short &y) {
    this->x = x;
    this->y = y;
    //display.drawRect(5, 5, 50, 50, BLACK);
    //display.refresh();
}

void PromptBox::setPromptText(String &promptStr) {
    this->promptStr = promptStr;
}

unsigned short int PromptBox::getX() {
    return x;
}

unsigned short int PromptBox::getY() {
    return y;
}