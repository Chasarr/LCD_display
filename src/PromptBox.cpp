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
    Button noBtn("No");
    Button yesBtn("Yes");
    pushGUI(yesBtn);
    pushGUI(noBtn);
    yesBtn.setPos(yesBtn.getXMin() + 4 * PADDING, yesBtn.getYMax() - yesBtn.getHeight() - PADDING);
    noBtn.setPos(noBtn.getXMax() - noBtn.getWidth() - 4 * PADDING, noBtn.getYMax() - noBtn.getHeight() - PADDING);
    Serial.println(yesBtn.getYMax());
    drawChildren();
    display.refresh();
    unsigned short int enter = 0;
    while (!enter) {
        enter = !digitalRead(ENTER_BTN);
        if (!digitalRead(LEFT_BTN)) {
            yesBtn.select();
            noBtn.deselect();
        } else if(!digitalRead(RIGHT_BTN)){
            noBtn.select();
            yesBtn.deselect();
        }
        drawChildren();
        display.refresh();
    }
    digitalWrite(LED_PIN, HIGH);
    delay(500000);

    /*for(;;) {
        display.clearDisplay();
        display.drawRoundRect(leftEdge, upperEdge, width, height, PADDING, BLACK);
        unsigned short int xRead = analogRead(ANALOG_X);
        unsigned short int yRead = analogRead(ANALOG_Y);
        yesBtn.setPos(xRead, yRead);
        drawChildren();
        Serial.print("xRead = ");
        Serial.print(xRead);
        Serial.print("\tyRead = ");
        Serial.println(yRead);

        display.refresh();
    }*/
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