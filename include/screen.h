#ifndef OLED_H
#define OLED_H

#include <U8g2lib.h>

#define OLED_CLOCK  15
#define OLED_DATA   4
#define OLED_RESET  16
#define OLED_WIDTH  g_OLED.getWidth()
#define OLED_HEIGHT g_OLED.getHeight()

class Screen {

public:
    int g_lineHeight = 0;
    void init_oled();
    void draw_oled();

private:
    // setting our OLED to use hardware mode
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R2, OLED_RESET, OLED_CLOCK, OLED_DATA);

}

#endif OLED_H
