#pragma once  //include guarding
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include "common.hpp"
#define X_MAX 400
#define Y_MAX 240
#define SHARP_SCK 21
#define SHARP_MOSI 14
#define SHARP_SS 32
#define BLACK 0
#define PADDING 10
#define WHITE 1



/**
 * Abstract parent class for graphics elements. Not sure if this should be included
 **/
class GUI {
public:
    GUI();
    virtual void draw(const unsigned short &x, const unsigned short &y) = 0;
    virtual short unsigned int getX() = 0;
    virtual short unsigned int getY() = 0;
    static Adafruit_SharpMem display;
protected:
    short unsigned int x = 0;
    short unsigned int y = 0;
    static boolean firstRun;
    void initializeGraphics();

};

/**
 * Asks user yes or no questions
 **/
class PromptBox : public GUI {
public:
    PromptBox(const char *promptString);
    void setPromptText(char *promptString);
    void draw(const unsigned short &x = 0, const unsigned short &y = 0) override;
    unsigned short int getX() override;
    unsigned short int getY() override;

private:
    char *promptString;
};