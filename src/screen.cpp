#include <screen.h>
#include <network.h>
 
void Screen::init_oled() {
  g_OLED.begin();
  g_OLED.clear();
  g_OLED.setFont(u8g2_font_profont15_tf);
  g_OLED.drawFrame(0, 0, OLED_WIDTH, OLED_HEIGHT);

  g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent();
}

void Screen::draw_oled() {
  g_OLED.clearBuffer();
  g_OLED.home();

  g_OLED.setCursor(3, g_lineHeight * 3 + 2);
  g_OLED.printf("IP: %s", WiFi.localIP().toString().c_str());

  g_OLED.sendBuffer();
}
