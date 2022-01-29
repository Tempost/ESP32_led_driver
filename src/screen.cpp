#include <screen.h>
#include <network.h>

#define OLED_WIDTH  OLED.getWidth()
#define OLED_HEIGHT OLED.getHeight()
#define OLED_RESET 16
#define OLED_CLOCK 15
#define OLED_DATA 4
    
uint16_t g_lineHeight = 0;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C OLED(U8G2_R2, OLED_RESET, OLED_CLOCK, OLED_DATA);

void init_screen() {
  OLED.begin();
  OLED.clear();
  OLED.setFont(u8g2_font_profont15_tf);
  OLED.drawFrame(0, 0, OLED_WIDTH, OLED_HEIGHT);

  g_lineHeight = OLED.getFontAscent() - OLED.getFontDescent();
}

void draw_screen(String ipAddr) {
  OLED.clearBuffer();
  OLED.home();

  OLED.setCursor(3, g_lineHeight * 3 + 2);
  OLED.printf("IP: %s", ipAddr.c_str());

  OLED.sendBuffer();
}
