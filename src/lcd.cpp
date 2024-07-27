#include "lcd.h"
#include "buzzer.h"

LCD::LCD() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

lcdStatus LCD::setupDisplay()
{   
    lcdStatus status;
    status = LCD_OK;
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) 
    {
        status = LCD_ERR;
        beepBuzzer(ERR_BEEP);
        Serial.println(F("SSD1306 allocation failed"));
        return status;
    }
    display.display();
    delay(1000);
    display.clearDisplay();
    beepBuzzer(OK_BEEP);
    return status;
}

void LCD::displayMessage(const char* message) 
{
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println(message);
    display.display();
}

void LCD::displayPercentage(float percentage) 
{
    display.clearDisplay();
    display.setCursor(20, 10);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("Measuring...");
    display.setCursor(20, 26);
    display.setTextSize(2);
    display.print((int)percentage);
    display.println("%");
    display.display();
}

void LCD::displayReadings(int heartRate, int spo2) 
{
    display.clearDisplay();
    display.drawBitmap(5, 5, logo2_bmp, 24, 21, WHITE);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(50,8);
    display.print(heartRate);
    display.println("bpm");
    display.setCursor(0,40);
    display.print("SPO2:");
    display.print(spo2);
    display.println("%");
    display.display();
}

void LCD::displayHeartBeat(int heartRate, int spo2) 
{
    display.clearDisplay();
    display.drawBitmap(0, 0, logo3_bmp, 32, 32, WHITE);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(50,8);
    display.print(heartRate);
    display.println("bpm");
    display.setCursor(0,40);
    display.print("SPO2:");
    display.print(spo2);
    display.println("%");
    display.display();
}

void LCD::displayFingerMessage() 
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30,10);
    display.println("Please Place ");
    display.setCursor(30,20);
    display.println("Your Finger ");
    display.display();
}

void LCD::clear() 
{
    display.clearDisplay();
}
