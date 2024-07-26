#include "buzzer.h"

void beepBuzzer(int beepNum) {
  static unsigned long previousMillis = 0;
  static int currentBeep = 0;
  static bool isBeeping = false;
  static bool isBuzzerOn = false;

  unsigned long currentMillis = millis();

  if (currentBeep < beepNum) 
  {
    if (isBeeping) 
    {
      if (currentMillis - previousMillis >= BEEP_DURATION) 
      {
        // Turn off the buzzer
        noTone(BUZZER_PIN);
        isBeeping = false;
        previousMillis = currentMillis; // Restart the interval timer
      }
    } 
    else 
    {
      if (currentMillis - previousMillis >= BEEP_INTERVAL) 
      {
        // Turn on the buzzer
        tone(BUZZER_PIN, 1000); // 1000 Hz tone frequency
        isBeeping = true;
        isBuzzerOn = true;
        currentBeep++;
        previousMillis = currentMillis; // Start the beep timer
      }
    }
  } 
  else 
  {
    // Ensure the buzzer is off after the final beep
    if (isBuzzerOn) 
    {
      noTone(BUZZER_PIN);
      isBuzzerOn = false;
    }
  }
}