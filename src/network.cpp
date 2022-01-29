#include <network.h>

// Stores LED state
String ledState;

// Replace with your network credentials
const char* ssid = "Diamond Home 2";
const char* password = "";

// Replaces placeholder with LED state value
// This sends data back to the webserver so we can see what happening on the hardware via the web interface
String processor(const String& var) {
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

void init_network() {
  // Create AsyncWebServer object on port 80
  AsyncWebServer server(80);

  // static IP setup
  IPAddress local_IP(192,168,1,100);
  IPAddress gateway(192,168,1,254);
  IPAddress subnet(255,255,0,0);

  // Initialize SPIFFS to access html content
  if(!SPIFFS.begin(true)){
    Serial.println("[ Error ] An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("[ INFO ] Connecting to WiFi...");
  }

  // setting a static IP address so we wont have to guess what IP it has been assigned
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("[ ERROR ] STA Failed to configure!");
  } else {
    Serial.printf("[ INFO ] Connected to wifi!\n IP: %s", WiFi.localIP().toString().c_str());
  }

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
