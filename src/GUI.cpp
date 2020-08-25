#include <utility>

#include "common.hpp"
#include "graphics.hpp"

bool GUI::firstRun = true;

GUI::GUI() {
    initializeGraphics();
}

GUI::~GUI() {
    GUIList.~list();
}

void GUI::setX(short unsigned int x) {
    xMax += x - xMin;
    xMin = x;
}

void GUI::setY(short unsigned int y) {
    yMax += y-yMin;
    yMin = y;
}

void GUI::setPos(unsigned short x, unsigned short y) {
    setX(x);
    setY(y);
}

short unsigned int GUI::getX() {
    return xMin;
}

short unsigned int GUI::getY() {
    return yMin;
}

void GUI::drawChildren() {
    // Iterate and draws objects in list
    for (GUI *element : GUIList) {
        element->draw();
    }

}

unsigned short int GUI::getWidth() const {
    return xMax - xMin;
}

unsigned short int GUI::getHeight() const {
    return yMax - yMin;
}

void GUI::setWidth(unsigned short int width) {
    xMax = xMin + width;
}

void GUI::setHeight(unsigned short int height) {
    yMax = yMin + height;
}

void GUI::pushGUI(GUI &guiElement) {
    GUIList.push_front(&guiElement);
    guiElement.setParent(this);
}

void GUI::setParent(GUI *parent) {
    this->parent = parent;
}

Adafruit_SharpMem GUI::display = Adafruit_SharpMem(SHARP_SCK, SHARP_MOSI, SHARP_SS, X_RES, Y_RES);

void GUI::initializeGraphics() {
    if (firstRun) {
        display.begin();
        display.clearDisplay();
        display.refresh();
        display.setTextSize(3);
        display.setTextColor(BLACK);
        display.setCursor(0, 0);
        display.cp437(true);
        display.setRotation(2);
    }
    firstRun = false;
}




