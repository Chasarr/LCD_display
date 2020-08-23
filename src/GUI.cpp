#include <utility>

#include "common.hpp"
#include "graphics.hpp"

boolean GUI::firstRun = true;

GUI::GUI() {
    initializeGraphics();
    xMin = 0;
    xMax = X_RES;
    yMin = 0;
    yMax = Y_RES;
}

GUI::~GUI() {
    GUIList.~list();
}

void GUI::setX(short unsigned int x) {
    this->x = x;
}

void GUI::setY(short unsigned int y) {
    this->y = y;
}

void GUI::setPos(unsigned short x, unsigned short y){
    setX(x);
    setY(y);
}

short unsigned int GUI::getX() {
    return x;
}

short unsigned int GUI::getY() {
    return y;
}

void GUI::drawChildren(){
    // Iterate and draws objects in list
    for (GUI *element : GUIList) {
        element->draw();
    }

}

unsigned short GUI::getWidth() const {
    return width;
}

unsigned short GUI::getHeight() const {
    return height;
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
        firstRun = false;
    }
}




