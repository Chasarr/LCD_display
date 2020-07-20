#include <utility>

#include "common.hpp"
#include "graphics.hpp"

GUI::GUI() {
    initializeGraphics();
}

boolean GUI::firstRun = true;
Adafruit_SharpMem GUI::display = Adafruit_SharpMem(SHARP_SCK, SHARP_MOSI, SHARP_SS, X_MAX, Y_MAX);
void GUI::initializeGraphics() {
    if (firstRun) {
        Serial.println("Initializing");
        display.begin();
        display.clearDisplay();
        display.refresh();
        display.setTextSize(3);
        display.setTextColor(BLACK);
        display.setCursor(0,0);
        display.cp437(true);
        display.setRotation(2);
        firstRun = false;
    } else {
        Serial.println("Not initializing");
    }
}

PromptBox::PromptBox(const char *promptString) : GUI() {
    this->promptString = const_cast<char *>(promptString);

}

void PromptBox::draw(const unsigned short &x, const unsigned short &y) {
    this->x = x;
    this->y = y;
    display.clearDisplay();
    display.drawRoundRect(PADDING, PADDING, X_MAX-2*PADDING, Y_MAX-2*PADDING, 20, BLACK);
    display.setCursor(PADDING*3, PADDING*3);
    Serial.println(display.write("Yes or no?"));
    display.drawLine(PADDING, PADDING*7, X_MAX-PADDING, PADDING*7, BLACK);

    display.refresh();
    delay(5000);
}

void PromptBox::setPromptText(char *promptString) {
    this->promptString = promptString;
}

unsigned short int PromptBox::getX() {
    return x;
}

unsigned short int PromptBox::getY() {
    return y;
}