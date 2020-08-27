/****************************************************
  Graphics library to display various GUI elements
 ****************************************************/

#pragma once  //include guarding

#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>
#include "common.hpp"
#include <list>
#include "img/Images.hpp"

#define X_RES 400       //Display width in pixels
#define Y_RES 240       //Display height in pixels
//Pin numbers to LCD display
#define SHARP_SCK 21
#define SHARP_MOSI 14
#define SHARP_SS 32
//Use BLACK and WHITE instead, since their numbering are somewhat unintuitive :D
#define BLACK 0
#define WHITE 1

#define PADDING 10      //Standardised padding to be used in all GUI elements. May or may not be appropriate to use


/**
 * Abstract parent class for graphics elements
 **/
class GUI {
public:

    /**
     * GUI constructor. MUST BE CALLED BY ALL CHILDREN IN THEIR CONSTRUCTOR!!!
     */
    GUI();

    /**
     * Destructor. Calling this function removes all children as well from GUIList
     */
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
     * @param x Input X coordinate
     * @param y Input Y coordinate
     */
    virtual void setPos(short unsigned int x, short unsigned int y);

    /**
     * Sets parent object. Some GUI elements contain other elements.
     * An example of this is the PromptBox, which contains two button objects with "Yes" or "No" answers
     * @param parent    Parent GUI object of this object
     */
    virtual void setParent(GUI *parent);

    /**
     * Please use this method instead of creating your own width and height variables
     * since it's only confusing to have multiple variables representing the same thing
     * @return  Width
     */
    unsigned short int getWidth() const;
    /**
     * Please use this method instead of creating your own width and height variables
     * since it's only confusing to have multiple variables representing the same thing
     * @return  Height
     */
    unsigned short int getHeight() const;

    /**
     * Set width here, which automatically changes xMax and yMax as well
     * @param width Returns width
     */
    void setWidth(unsigned short int width);
    /**
     * Set height here, which automatically changes xMax and yMax as well
     * @param height Returns height
    */
    void setHeight(unsigned short int height);

protected:
    static Adafruit_SharpMem display;       //Static display-object. This contains basic functions to draw various shapes

    std::list<GUI *> GUIList;               //List of all children

    //Boundary box for the GUI element
    unsigned short int xMax = X_RES;
    unsigned short int yMax = Y_RES;
    unsigned short int xMin = 0;
    unsigned short int yMin = 0;

    /**
     * Draws all objects from GUIList
     */
    void drawChildren();

    /**
     * Adds a child GUI element. Please use this function instead of managing GUI objects by yourself, since it makes garbage collection easier
     * @param guiElement
     */
    void pushGUI(GUI &guiElement);

private:
    static bool firstRun;                //Indicates if any GUI object has been initialized before. If so a new static display-object is initialized
    static void initializeGraphics();       //Initializes all graphic components if firstRun == true
    GUI *parent;                            //Parent object. Can be null


};

/**
 * Asks user yes or no questions
 **/
class PromptBox : public GUI {
public:
    PromptBox(const char *promptString);

    /**
     * Manually input prompt text
     * @param promptString  Question to be asked to the user
     */
    void setPromptText(const char *promptString);

    /**
     * Use the 'prompt()' function instead if you want to recieve the users answer
     * This function only draws the promptBox, but it doesn't return any answer.
     */
    void draw() override;

    /**
     * Use this instead of draw(). Returns yes or no value
     * @return
     */
    boolean prompt();

private:
    char *promptString;     //Question to be asked to the user

};

/**
 * Asks user yes or no questions
 **/
class Button : public GUI {
public:
    /**
     * Initializes the button
     * @param btnTxt    Text to be displayed on the button
     */
    Button(char *btnTxt);

    /**
     * You can change the button text here again
     * @param btnTxt        Text to be displayed in the button
     */
    void setBtnTxt(char *btnTxt);

    /**
     * Selects the button. Must be redrawn with display.refresh()
     */
    void select();

    /**
     * Deselects the button. Must be redrawn with display.refresh()
     */
    void deselect();

    /**
     * Draws the button
     */
    void draw() override;

    /**
     * Returns whether or not the button is selected
     * @return     bool value if the button is selected
     */
    bool getSelected();

private:
    boolean selected = false;
    char *btnTxt;       //Button text
};

/**
 * A list which can be scrolled through
 * TODO make the list scroll past the display resolution limits
 */
class ScrollList : public GUI{
public:
    /**
     * Initializes the scroll list with default size
     * @param scrollStrings Array with text
     * @param size Size of the array
     */
    ScrollList(const char* scrollStrings[], unsigned short int size);

    /**
     * Initializes the scroll list with custom size
     * Use with caution, since it's not guranteed to scale well
     * @param scrollStrings Array with text
     * @param size Size of the array
     * @param minX
     * @param minY
     * @param maxX
     * @param maxY
     */
    ScrollList(const char* scrollStrings[], unsigned short int size, unsigned short int minX, unsigned short int minY, unsigned short int maxX, unsigned short int maxY);
    ~ScrollList();

    /**
     * Draws the scroll list. USE prompt() INSTEAD
     * otherwise it won't return user input
     */
    void draw() override;

    /**
     * Prompts and draws the scroll list
     * @return User input
     */
    unsigned short int prompt();

    /**
     * Returns size of scroll list
     * @return Size of scroll list
     */
    unsigned short int getSize();

private:
    enum direction { up = -1, down = 1};    //Makes the code a bit easier to understand
    const char** scrollStrings;         //Array with all text
    unsigned short int size;            //Size of array
    void scroll(direction scrollDir);   //Scroll function which is called when one of the buttons are pressed
    unsigned short int selected;        //Number of the currently selected item
    unsigned short int boxHeight;       //Height of each option box
};

/**
 * Displays a grid of elements to pick from
 */
class MainMenu : public GUI{
public:
    /**
     * Initializes the menu
     */
    MainMenu();

    /**
     * Draws the menu. USE prompt() INSTEAD
     */
    void draw();

    /**
     * Selects an icon and and displays it to the user
     * @param selected Selected item box
     */
    void select(unsigned short selected);

    /**
     * Draws a single icon
     * @param iconNumber Number from between 0 and 99999999999999999...
     * @param selected Is the box selected?
     */
    void drawIcon(unsigned short iconNumber, bool selected = false);

    /**
     * Draws a single icon
     * @param column Column of the item
     * @param row   Row of the item
     * @param selected Is the box selected?
     */
    void drawIcon(unsigned short column, unsigned short row, bool selected = false);
    /**
     * Prompts the user for a menu input
     * @return User input
     */
    unsigned short prompt();
private:
    unsigned short selected = 0;
};