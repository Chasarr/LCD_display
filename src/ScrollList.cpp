#include "common.hpp"
#include <list>


ScrollList::ScrollList(const char *scrollStrings[], unsigned short int size) : GUI(){
    this->scrollStrings = scrollStrings;
    xMin = PADDING;
    yMin = PADDING;
    xMax = X_RES - PADDING;
    yMax = Y_RES - PADDING;
    this->size = size;
    selected = 0;
    boxHeight = 40;
}

ScrollList::ScrollList(const char *scrollStrings[], unsigned short int size, unsigned short int xMin,
                       unsigned short int yMin, unsigned short int xMax, unsigned short int yMax) : GUI(){
    this->scrollStrings = scrollStrings;
    this->xMin = xMin;
    this->xMax = xMax;
    this->yMin = yMin;
    this->yMax = yMax;
    this->size = size;
}


ScrollList::~ScrollList() {}


void ScrollList::draw() {
    prompt();
}

unsigned short int ScrollList::prompt(){
    display.fillRect(xMin, yMin, getWidth(), getHeight(), WHITE);
    display.fillRect(xMin, yMin, getWidth(), boxHeight, BLACK);
    display.setTextColor(WHITE);
    display.setCursor(xMin + PADDING, yMin + PADDING);
    display.write(scrollStrings[selected]);
    display.setTextColor(BLACK);
    for (unsigned short int i = 1; i < size; i++) {
        digitalWrite(LED_PIN, HIGH);
        unsigned short int yPosBox = yMin + i * boxHeight;
        display.drawRect(xMin, yPosBox, getWidth(), boxHeight, BLACK);
        display.setCursor(xMin + PADDING, yPosBox + PADDING);
        display.write(scrollStrings[i]);
    }
    display.refresh();
    Debounce btnLeft(LEFT_BTN, true);
    Debounce btnEnter(ENTER_BTN, true);
    Debounce btnRight(RIGHT_BTN, true);
    while (!btnEnter.update()) {
        if (btnLeft.update() && selected > 0) {
            scroll(up);
        }
        if (btnRight.update() && selected < size - 1) {
            scroll(down);
        }
    }
    display.fillRect(xMin, yMin, getWidth(), getHeight(), WHITE);
    return selected;
}


unsigned short int ScrollList::getSize() {
    return size;
}

void ScrollList::scroll(direction scrollDir) {
    unsigned short int yPosBox;
    bool color = BLACK;

    for (unsigned short int i = 0; i < 2; i++) {
        selected = selected + i * scrollDir;
        yPosBox = yMin + selected * boxHeight;
        color = !color;
        display.fillRect(xMin, yPosBox, getWidth(), boxHeight, color);
        display.drawRect(xMin, yPosBox, getWidth(), boxHeight, !color);
        display.setTextColor(!color);
        display.setCursor(xMin + PADDING, yPosBox + PADDING);
        display.write(scrollStrings[selected]);
    }
    display.refresh();
}