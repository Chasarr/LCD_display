#include "common.hpp"


PromptBox::PromptBox(const char *promptString) : GUI() {
    setPromptText(promptString);
    xMin = PADDING;
    xMax = X_RES - PADDING;
    yMin = PADDING;
    yMax = Y_RES - PADDING;


}

void PromptBox::draw() {
    prompt();
}

boolean PromptBox::prompt(){
    display.fillRoundRect(PADDING, PADDING, getWidth(), getHeight(), 20, WHITE);
    display.drawRoundRect(PADDING, PADDING, getWidth(), getHeight(), 20, BLACK);
    display.setCursor(PADDING * 3, PADDING * 3);
    display.write(promptString);
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
            drawChildren();
            display.refresh();
        } else if (!digitalRead(RIGHT_BTN)) {
            noBtn.select();
            yesBtn.deselect();
            drawChildren();
            display.refresh();
        }
    }
    return yesBtn.getSelected();
}

void PromptBox::setPromptText(const char *promptString) {
    this->promptString = const_cast<char *>(promptString);
}