#include <network.h>
#include <screen.h>

#define OLED_CLOCK  15
#define OLED_DATA   4
#define OLED_RESET  16

// Set LED Pin
#define LED_PIN  5

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  init_network();
  init_screen();

  // might init led info here?
}
 
void loop(){
  for (;;) {
    static unsigned long msLastUpdate = millis();
    if (millis() - msLastUpdate > 250) {
      draw_screen(WiFi.localIP().toString());
    }
  }
}
