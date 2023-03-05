#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
//#include "env.h"

#define pinkLED 18
#define redLED 19
#define blueLED 21

char * endpoint = "https://ecse-three-led-api-v2.onrender.com";
const char * WIFI_SSID = "Wokwi-GUEST";
const char * WIFI_PASS = "";
const char * key = "Susannah#9481";

bool data [8][3] = {
  {false, false, false},
  {false, false, true},
  {false, true, false},
  {false, true, true},
  {true, false, false},
  {true, false, true},
  {true, true, false},
  {true, true, true},
};

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  pinMode(pinkLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(endpoint);

    for(int b = 0; b < 8; b++){

      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-API-Key", key);

    StaticJsonDocument<102> doc;
    String httpRequestData;

    digitalWrite(redLED, data[b][0]);
    digitalWrite(pinkLED, data[b][1]);
    digitalWrite(blueLED, data[b][2]);
    
    doc["redLED"] = data[b][0];
    doc["pinkLED"] = data[b][1];
    doc["blueLED"] = data[b][2];

    serializeJson(doc, httpRequestData);    

    int httpResponseCode = http.PUT(httpRequestData);
    String http_response;
     
      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);
      
      http_response = http.getString();
      Serial.println(http_response);
 
      http.end();
    
    delay(2000);
    }
  
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  }
