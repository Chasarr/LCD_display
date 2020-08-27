#pragma once

#include <Arduino.h>
#include <common.hpp>

#define SOUND_PWM_CHANNEL   0
#define SOUND_RESOLUTION    8 // 8 bit resolution
#define SOUND_ON            (1<<(SOUND_RESOLUTION-1)) // 50% duty cycle
#define SOUND_OFF           0                         // 0% duty cycle

TaskHandle_t soundTask;

void asyncToneMiddleMan(void *params);


/**
 * //Creates a beep sound if a piezo electric speaker is connected
 * @param pin               Which pin is the speaker connected to?
 * @param frequency         Which frequency/tone should the speaker play?
 * @param duration          How long should the speaker play the sound?
 */
void tone(unsigned short int pin, unsigned short int frequency, unsigned short int duration) {
    ledcSetup(SOUND_PWM_CHANNEL, frequency, SOUND_RESOLUTION);  // Set up PWM channel
    ledcAttachPin(pin, SOUND_PWM_CHANNEL);                      // Attach channel to pin
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_ON);
    delay(duration);
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_OFF);
}

/**
 * Plays sound on the second core asynchronously
 */
void asyncTone() {

    xTaskCreatePinnedToCore(
            asyncToneMiddleMan, /* Function to implement the task */
            "soundTask", /* Name of the task */
            10000,  /* Stack size in words */
            NULL,  /* Task input parameter */
            0,  /* Priority of the task */
            &soundTask,  /* Task handle. */
            0); /* Core where the task should run */
}

/**
 * This acts as a middle man for the multithreading
 * The function cretes a tone and then shuts itself down
 * @param params What the heck does this even do lol
 */
void asyncToneMiddleMan(void *params) {
    tone(BEEP_PIN);
    vTaskDelete(NULL);
}

