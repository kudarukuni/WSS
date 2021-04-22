#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

AsyncWebServer server(80);
int sensor = 13;

String readMotion() {
  long state = digitalRead(sensor);
  return String(state);
}

void setup(){
  pinMode(sensor, INPUT);
  Serial.begin(115200);
  Serial.println();
  
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/motion", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readMotion().c_str());
  });

  server.begin();
}
 
void loop(){
  if (digitalRead(sensor) == HIGH) {
    Serial.println("Activity");
    delay(500);
  }
  else {
    Serial.println(" ");
    delay(500);
  }
}
