#include "common.hpp"

#define COLUMN_NBR 4
#define ROW_NBR 3
const unsigned short size = ROW_NBR * COLUMN_NBR;

MainMenu::MainMenu() : GUI() {}

void MainMenu::draw() {

}

unsigned short MainMenu::prompt(){
    display.clearDisplay();
    bool sel = true;
    for (unsigned short i = 0; i < 4; i++) {
        for (unsigned short j = 0; j < 3; j++) {
            drawIcon(i, j, sel);
            sel = false;
        }
    }
    display.refresh();
    Debounce btnLeft(LEFT_BTN, true);
    Debounce btnEnter(ENTER_BTN, true);
    Debounce btnRight(RIGHT_BTN, true);
    while (!btnEnter.update()) {
        if (btnLeft.update() && selected > 0) {
            select(selected - 1);
        }
        if (btnRight.update() && selected < size - 1) {
            select(selected + 1);
        }
    }
    return selected;
}

void MainMenu::select(unsigned short selected) {
    unsigned short column = this->selected % COLUMN_NBR;
    unsigned short row = this->selected / COLUMN_NBR;
    asyncTone();

    bool color = WHITE;
    for (unsigned short i = 0; i < 2; i++) {
        display.fillRect(PADDING * (column + 1) + column * 64 - PADDING / 2,
                         PADDING * (row + 1) + row * 64 - PADDING / 2,
                         calcIcon.width + PADDING, calcIcon.height + PADDING, color);
        display.drawXBitmap(PADDING * (column + 1) + column * 64, PADDING * (row + 1) + row * 64,
                            calcIcon.bitmap, calcIcon.width, calcIcon.height, !color);
        column = selected % COLUMN_NBR;
        row = selected / COLUMN_NBR;
        color = !color;
    }
    this->selected = selected;
    display.refresh();

}

void MainMenu::drawIcon(unsigned short iconNumber, bool selected) {
    unsigned short column = iconNumber % COLUMN_NBR;
    unsigned short row = iconNumber / ROW_NBR;
    drawIcon(column, row, selected);

}

void MainMenu::drawIcon(unsigned short column, unsigned short row, bool selected) {
    bool color = selected;

    display.fillRect(PADDING * (column + 1) + column * 64 - PADDING / 2, PADDING * (row + 1) + row * 64 - PADDING / 2,
                     calcIcon.width + PADDING, calcIcon.height + PADDING, !color);
    display.drawXBitmap(PADDING * (column + 1) + column * 64, PADDING * (row + 1) + row * 64,
                        calcIcon.bitmap, calcIcon.width, calcIcon.height, color);
}