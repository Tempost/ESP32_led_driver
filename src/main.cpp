#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#include <U8g2lib.h>

#define OLED_CLOCK  15
#define OLED_DATA   4
#define OLED_RESET  16
#define OLED_WIDTH  g_OLED.getWidth()
#define OLED_HEIGHT g_OLED.getHeight()

// Set LED GPIO
#define LED_PIN  2

// Replace with your network credentials
const char* ssid = "Diamond Home 2";
const char* password = "";

// Stores LED state
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// static IP setup
IPAddress local_IP(192,168,1,100);
IPAddress gateway(192,168,1,254);
IPAddress subnet(255,255,0,0);

// setting our OLED to use hardware mode
U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R2, OLED_RESET, OLED_CLOCK, OLED_DATA);

int g_lineHeight = 0;

// Replaces placeholder with LED state value
// This sends data back to the webserver so we can see what happening on the hardware via the web interface
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(LED_BUILTIN)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  g_OLED.begin();
  g_OLED.clear();
  g_OLED.setFont(u8g2_font_profont15_tf);
  g_OLED.drawFrame(0, 0, OLED_WIDTH, OLED_HEIGHT);

  g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent();

  // might init led info here?

  // Initialize SPIFFS to access html content
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("[ INFO ] Connecting to WiFi...");
  }

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("[ ERROR ] STA Failed to configure!");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_BUILTIN, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED_BUILTIN, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}
