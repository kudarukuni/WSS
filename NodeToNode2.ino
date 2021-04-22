#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";
const char* serverNameMotion = "http://192.168.4.1/motion";

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String motion;
unsigned long previousMillis = 0;
const long interval = 5500; 

void setup(){
  Serial.begin(115200);
  Serial.println();
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
  while((WiFiMulti.run() == WL_CONNECTED)) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      motion = httpGETRequest(serverNameMotion);
      Serial.println("Motion: " + motion);
      
      display.clearDisplay();
      display.setTextSize(4);
      display.setCursor(0,0);
      display.print("Motion: ");
      display.print(motion);
      
      display.display();
      
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);

  int httpResponseCode = http.GET();
  String payload = "--"; 
  
  if (httpResponseCode > 0) {
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}
