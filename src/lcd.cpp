#include "lcd.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupDisplay()
{

}

void displayData(uint16_t spo2, uint8_t validSpo2, int32_t heartRate, int8_t validHeartRate)
{
    
}