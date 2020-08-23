/****************************************************
  Graphics library to display various GUI elements
 ****************************************************/

#pragma once  //include guarding

#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include "common.hpp"
#include <list>

#define X_RES 400
#define Y_RES 240
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

    ~GUI();

    /**
     * All GUI objects must be able to be drawn, and must use this function
     */
    virtual void draw() = 0;

    /**
     * @return X    Get X position
     */
    virtual short unsigned int getX();

    /**
     * @return Get Y position
     */
    virtual short unsigned int getY();

    /**
     * @param x     Input X coordinate
     */
    virtual void setX(short unsigned int x);

    /**
     * @param y     Input Y coordinate
     */
    virtual void setY(short unsigned int y);

    /**
     * Sets both X and Y position simultaneously
     * @param x
     * @param y
     */
    virtual void setPos(short unsigned int x, short unsigned int y);

    /**
     * Sets parent object. Some GUI elements contain other elements.
     * An example of this is the PromptBox, which contains two button objects with "Yes" or "No" answers
     * @param parent    Parent GUI object of this object
     */
    virtual void setParent(GUI *parent);

    unsigned short getWidth() const;

    unsigned short getHeight() const;

protected:
    static boolean firstRun;
    static Adafruit_SharpMem display;
    short unsigned int x = 0;
    short unsigned int y = 0;
    //This is the "child space", where the children can operate
    /*short unsigned int leftEdge;
    short unsigned rightEdge;
    short unsigned upperEdge;
    short unsigned lowerEdge;*/
    std::list<GUI *> GUIList;
    //By default the object is top-level and has same constraints as display res
    unsigned short int xMax;// = X_RES;
    unsigned short int yMax;    // = Y_RES;
    unsigned short int xMin;
    unsigned short int yMin;

    unsigned short int width;
    unsigned short int height;

    void initializeGraphics();

    void drawChildren();

    void pushGUI(GUI &guiElement);

private:

    GUI *parent;


};

/**
 * Asks user yes or no questions
 **/
class PromptBox : public GUI {
public:
    PromptBox(const char *promptString);

    void setPromptText(char *promptString);

    void draw() override;

    unsigned short int getX() override;

    unsigned short int getY() override;


private:
    char *promptString;
    unsigned short int width = xMax - 2 * PADDING;
    unsigned short int height = yMax - 2 * PADDING;
};

/**
 * Asks user yes or no questions
 **/
class Button : public GUI {
public:
    Button(char *btnTxt);

    void setBtnTxt(char *btnTxt);

    void select();

    void deselect();

    void draw() override;

    unsigned short int getX() override;

    unsigned short int getY() override;

    boolean getSelected();

private:
    boolean selected = false;
    char *btnTxt;
};