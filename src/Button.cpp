#include "common.hpp"


Button::Button(char *btnTxt) {
    this->btnTxt = btnTxt;
    width = 100;
    height = 40;
}

void Button::setBtnTxt(char *btnTxt) {
    this->btnTxt = btnTxt;
}

void Button::draw() {
    display.setCursor(getX() + 2 * PADDING, getY() + PADDING);

    if (selected) {
        display.setTextColor(WHITE);
        display.fillRoundRect(x, y, width, height, PADDING, BLACK);
        display.write(btnTxt);
    } else {
        display.setTextColor(BLACK);
        display.fillRoundRect(x, y, width, height, PADDING, WHITE);
        display.drawRoundRect(x, y, width, height, PADDING, BLACK);
        display.write(btnTxt);
    }
}


unsigned short int Button::getX() {
    return x;
}

unsigned short int Button::getY() {
    return y;
}

void Button::select() {
    selected = true;
}

void Button::deselect() {
    selected = false;
}

boolean Button::getSelected() {
    return selected;
}