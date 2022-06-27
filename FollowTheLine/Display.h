#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C

class Display {
private:
  Adafruit_SSD1306 lcd = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  
public:
  Display() {   
    if(!lcd.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      for(;;); // Don't proceed, loop forever
    }
    drawText("LCD Enabled", 1, 0, 0);
  }

  // Draw text to the arduino display. String tekst, bool clearDisp, int x, int y, int textSize
  void drawText(String text, int textSize, int x, int y) {
    lcd.clearDisplay();

    lcd.setTextSize(textSize);
    lcd.setTextColor(SSD1306_WHITE);
    lcd.setCursor(x, y);
    lcd.println(text);
    lcd.display();    
  }
};
