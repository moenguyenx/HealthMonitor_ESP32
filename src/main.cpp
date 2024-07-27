#include <Wire.h>
#include <Arduino.h>
#include "lcd.h"
#include "sensor.h"
#include "buzzer.h"

LCD lcd;
HeartRateSensor sensor;

int32_t bufferLength = 100;
int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;

void setup() 
{
    Serial.begin(115200);
    Wire.begin();   

    // Initialize SSD1306
    if(lcd.setupDisplay() == LCD_OK)
    { 
      lcd.displayMessage("Display OK");
    }
    delay(1000);

    // Initialize MAX30102
    if(sensor.begin() == SENSOR_OK)
    {
      lcd.displayMessage("Sensor  OK");
    }
    else
    {
      lcd.displayMessage("Sensor  ERROR");
    }
    delay(1000);

    lcd.displayMessage("System  OK");
    beepBuzzer(OK_BEEP);
    delay(1000);
}

void loop() 
{
  lcd.clear();
  long irValue = sensor.readIR();
  
  if (irValue > 7000) 
  {
    tone(5, 1000, 100); // Beep once when finger is detected

    sensor.readSamples(bufferLength, lcd);
    
    sensor.calculate(bufferLength, &spo2, &validSPO2, &heartRate, &validHeartRate);
    
    while(1)
    {
      irValue = sensor.readIR();
      if (irValue <= 7000) {
        Serial.println("Finger removed. Exiting measurement loop.");
        break;
      }

      sensor.continuousSampling();

      lcd.displayReadings(heartRate, spo2);

      if (checkForBeat(irValue)) 
      {
        lcd.displayHeartBeat(heartRate, spo2);
      }
      sensor.calculate(bufferLength, &spo2, &validSPO2, &heartRate, &validHeartRate);
    }
  } 
  else 
  {
    lcd.displayFingerMessage();
  }
}