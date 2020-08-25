#pragma once


#include <Arduino.h>
#include "graphics.hpp"
#include <string>
#include "Debounce.hpp"
#include "img/Images.hpp"



// any pins can be used

#define BEEP_PIN 25
#define LEFT_BTN 15
#define ENTER_BTN 27
#define RIGHT_BTN 13
#define ANALOG_X 34
#define ANALOG_Y 26
#define LED_PIN 33


void tone(unsigned short int pin, unsigned short int frequency = 440, unsigned short int duration = 50);



