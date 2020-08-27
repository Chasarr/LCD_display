#pragma once


#include <Arduino.h>
#include "graphics.hpp"
#include <string>
#include "Debounce.hpp"
#include "img/Images.hpp"
#include "soundList.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"



// any pins can be used

#define BEEP_PIN 25
#define LEFT_BTN 15
#define ENTER_BTN 27
#define RIGHT_BTN 13
#define ANALOG_X 34
#define ANALOG_Y 26
#define LED_PIN 33

/**
 * Creates a tone
 * @param pin Speaker pin number
 * @param frequency Sound frequency
 * @param duration How long the speaker should run for
 */
void tone(unsigned short int pin = BEEP_PIN, unsigned short int frequency = 440, unsigned short int duration = 50);

/**
 * Creates a sound from the ESP32's other otherwise unused core
 */
void asyncTone();



