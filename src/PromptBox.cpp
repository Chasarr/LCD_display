#include "common.hpp"

PromptBox::PromptBox(const char *promptString) : GUI() {
    this->promptString = const_cast<char *>(promptString);
}

void PromptBox::draw() {
    this->x = x;
    this->y = y;
    display.fillRoundRect(PADDING, PADDING, width, height, 20, WHITE);
    display.drawRoundRect(PADDING, PADDING, width, height, 20, BLACK);
    display.setCursor(PADDING * 3, PADDING * 3);
    Serial.println(display.write(promptString));
    display.drawLine(PADDING, PADDING * 7, X_RES - PADDING, PADDING * 7, BLACK);
    Button noBtn("No");
    Button yesBtn("Yes");
    pushGUI(yesBtn);
    pushGUI(noBtn);
    yesBtn.setPos(5 * PADDING, Y_RES - yesBtn.getHeight() - PADDING * 3);
    noBtn.setPos(X_RES - 5 * PADDING - noBtn.getWidth(), Y_RES - noBtn.getHeight() - PADDING * 3);
    drawChildren();
    display.refresh();
    unsigned short int enter = 0;
    while (!enter) {
        enter = !digitalRead(ENTER_BTN);
        if (!digitalRead(LEFT_BTN)) {
            yesBtn.select();
            noBtn.deselect();
        } else if (!digitalRead(RIGHT_BTN)) {
            noBtn.select();
            yesBtn.deselect();
        }
        drawChildren();
        display.refresh();
    }
    digitalWrite(LED_PIN, HIGH);
    delay(500000000);

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