#include <network.h>
#include <screen.h>

// Set LED Pin
#define LED_PIN  5

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Network wifi;

  wifi.init();
  init_oled();

  // might init led info here?
}
 
void loop(){
  for (;;) {
    static unsigned long msLastUpdate = millis();
    if (millis() - msLastUpdate > 250) {
      draw_oled();
    }
  }
}
