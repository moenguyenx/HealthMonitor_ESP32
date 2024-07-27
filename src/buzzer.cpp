#include "buzzer.h"

void beepBuzzer(int beepNum) 
{
    unsigned long previousMillis = 0;
    int currentBeep = 0;

    while (currentBeep < beepNum) 
    {
        unsigned long currentMillis = millis();
        if(currentMillis - previousMillis >= BEEP_INTERVAL)
        {
            tone(BUZZER_PIN, 1000, BEEP_DURATION);
            previousMillis = currentMillis;
            currentBeep++;
        }
    } 
}