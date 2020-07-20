#include "common.hpp"

PromptBox::PromptBox(const char *promptString) : GUI() {
    this->promptString = const_cast<char *>(promptString);
    leftEdge = PADDING;
    rightEdge = xMax - PADDING;
    upperEdge = PADDING;
    lowerEdge = yMax - PADDING;
}

void PromptBox::draw() {
    this->x = x;
    this->y = y;
    display.clearDisplay();
    display.drawRoundRect(leftEdge, upperEdge, width, height, 20, BLACK);
    display.setCursor(PADDING * 3, PADDING * 3);
    Serial.println(display.write("Yes or no?"));
    display.drawLine(leftEdge, PADDING * 7, rightEdge, PADDING * 7, BLACK);
    Button yesBtn("Yes");
    Serial.print("Sanity check of sanity check: leftEdge = ");
    Serial.println(leftEdge);
    pushGUI(yesBtn);
    drawChildren();
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