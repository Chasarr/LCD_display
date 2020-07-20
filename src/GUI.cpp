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

short unsigned int GUI::getX() {
    return x;
}

short unsigned int GUI::getY() {
    return y;
}

short unsigned int GUI::getLeftEdge() {
    return leftEdge;
}

short unsigned int GUI::getRightEdge() {
    return rightEdge;
}

short unsigned int GUI::getUpperEdge() {
    return upperEdge;
}

short unsigned int GUI::getLowerEdge() {
    return lowerEdge;
}
void GUI::drawChildren(){
    // Iterate and draws objects in list
    for (GUI *element : GUIList) {
        element->draw();
    }

}


void GUI::pushGUI(GUI &guiElement) {
    Serial.print("Sanity check, leftEdge = ");
    Serial.println(leftEdge);
    GUIList.push_front(&guiElement);


    guiElement.setParent(this);

}

void GUI::setParent(GUI *parent) {
    this->parent = parent;
    Serial.print("Setting xMin with parent->getLeftEdge(). which is equal to ");
    Serial.println(parent->getLeftEdge());
    xMin = parent->getLeftEdge();
    xMax = parent->getRightEdge();
    yMin = parent->getUpperEdge();
    yMax = parent->getLowerEdge();
}

Adafruit_SharpMem GUI::display = Adafruit_SharpMem(SHARP_SCK, SHARP_MOSI, SHARP_SS, X_RES, Y_RES);

void GUI::initializeGraphics() {
    if (firstRun) {
        Serial.println("Initializing");
        display.begin();
        display.clearDisplay();
        display.refresh();
        display.setTextSize(3);
        display.setTextColor(BLACK);
        display.setCursor(0, 0);
        display.cp437(true);
        display.setRotation(2);
        firstRun = false;
    } else {
        Serial.println("Not initializing");
    }
}




