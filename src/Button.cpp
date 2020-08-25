#include "common.hpp"


Button::Button(char *btnTxt) : GUI() {
    this->btnTxt = btnTxt;
    setWidth(100);
    setHeight(40);
}

void Button::setBtnTxt(char *btnTxt) {
    this->btnTxt = btnTxt;
}

void Button::draw() {
    display.setCursor(getX() + 2 * PADDING, getY() + PADDING);
    Serial.print("getHeight() = ");
    Serial.print(getHeight());
    Serial.print(", yMin = ");
    Serial.print(yMin);
    Serial.print(", yMax = ");
    Serial.println(yMax);

    if (selected) {
        display.setTextColor(WHITE);
        display.fillRoundRect(xMin, yMin, getWidth(), getHeight(), PADDING, BLACK);
        display.write(btnTxt);
    } else {
        display.setTextColor(BLACK);
        display.fillRoundRect(xMin, yMin, getWidth(), getHeight(), PADDING, WHITE);
        display.drawRoundRect(xMin, yMin, getWidth(), getHeight(), PADDING, BLACK);
        display.write(btnTxt);
    }
}

void Button::select() {
    selected = true;
}

void Button::deselect() {
    selected = false;
}

bool Button::getSelected() {
    return selected;
}