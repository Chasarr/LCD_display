#include "common.hpp"


Button::Button(char *btnTxt) {
    this->btnTxt = btnTxt;
}

void Button::setBtnTxt(char *btnTxt) {
    this->btnTxt = btnTxt;
}

void Button::draw() {
    Serial.print("xMin = ");
    Serial.println(xMin);
    display.drawRoundRect(xMin + x, yMin + y, 100, 40, 20, BLACK);
}

unsigned short int Button::getX() {
    return x;
}

unsigned short int Button::getY() {
    return y;
}