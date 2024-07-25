#include "lcd.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupDisplay()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) 
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
}

void displayData(uint16_t spo2, uint8_t validSPO2, int32_t heartRate, int8_t validHeartRate)
{
    display.clearDisplay();
    display.setCursor(0, 0);

    display.print("HR=");
    display.print(heartRate);
    display.print(" bpm");

    display.print("\nSPO2=");
    display.print(spo2);
    display.print(" %");

    if (!validSPO2 || !validHeartRate) 
    {
        display.clearDisplay();
        display.setCursor(30,5);
        display.println("Please Place ");
        display.setCursor(30,15);
        display.println("Your Finger ");
        display.display();
        noTone(13);
    }

    display.display();
}