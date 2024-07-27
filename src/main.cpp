#include <Wire.h>
#include <Arduino.h>
#include "lcd.h"
#include "sensor.h"
#include "buzzer.h"

LCD             lcd;
HeartRateSensor sensor;

int32_t         bufferLength = 100; // Buffer length of 100 stores 4 seconds of samples running at 25sps
int32_t         spo2;
int8_t          validSPO2;
int32_t         heartRate;
int8_t          validHeartRate;

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

    lcd.displayMessage("System  OK");
    beepBuzzer(OK_BEEP);
    delay(1000);

    // Initialize MAX30102
    if(sensor.begin() == SENSOR_OK)
    {
        lcd.displayMessage("Sensor  OK");
    }
    else
    {
        lcd.displayMessage("Sensor  ERROR");
        delay(1000);
        lcd.displayMessage("");
        lcd.displayMessage("Startup ERROR");
        lcd.displayMessage("Check Wiring!");
        beepBuzzer(ERR_BEEP);
        for(;;);
    }
    delay(1000);
}

void loop() 
{
    lcd.clear();

    // Check if Finger is detected
    long irValue = sensor.readIR();
    
    if (irValue > 7000) 
    {
        // Beep once when finger is detected
        tone(BUZZER_PIN, 1000, BEEP_DURATION);
  
        // Read the first 100 samples, and determine the signal range
        sensor.readSamples(bufferLength, lcd);
        sensor.calculate(bufferLength, &spo2, &validSPO2, &heartRate, &validHeartRate);

        while(1)
        {
            irValue = sensor.readIR();
            if (irValue <= 7000) 
            {
                Serial.println("Finger removed. Exiting measurement loop.");
                break;
            }

            //Continuously taking samples from MAX30102. Heart rate and SpO2 are calculated every 1 second
            sensor.continuousSampling();

            lcd.displayHeartBeat(heartRate, spo2);
            lcd.displayReadings(heartRate, spo2);
            tone(BUZZER_PIN, 1000, BEEP_DURATION);

            sensor.calculate(bufferLength, &spo2, &validSPO2, &heartRate, &validHeartRate);
        }
    } 
    else 
    {
        lcd.displayFingerMessage();
    }
}