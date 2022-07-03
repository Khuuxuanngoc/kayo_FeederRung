#include "Vietduino_Manager_Priority.h"
#include "Vietduino_Led.h"
#include "Vietduino_Button.h"
#include "PinVar.h"

#include "OTA_AccessPoint.h"

// #include "Arduino.h"
// #if defined(ESP8266)
//   #include <ESP8266WiFi.h>
//   #include <ESPAsyncTCP.h>
// #elif defined(ESP32)
//   #include <WiFi.h>
//   #include <AsyncTCP.h>
// #endif

// #include <ESPAsyncWebServer.h>
// #include <AsyncElegantOTA.h>

Vietduino_Led feeder(PIN_FEEDER, SIG_ACTIVE_FEEDER);
Vietduino_Button ds30c4;

// const char* ssid = "noFree";
// const char* password = "likehshop";

// AsyncWebServer server(80);

// void OTA_AccessPoint_Init(){
//     /* You can remove the password parameter if you want the AP to be open. */
//     WiFi.mode(WIFI_AP_STA);

//     WiFi.softAP(ssid, password);

//     IPAddress myIP = WiFi.softAPIP();

//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//         request->send(200, "text/plain", "Hi! This is a sample response.");
//     });

//     AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
//     server.begin();
// }

void setup()
{
    ds30c4.begin(PIN_SENSOR, SIG_ACTIVE_SENSOR);
    ds30c4.setPressTicks(100);

    Serial.begin(115200);
    Serial.println(F("Start"));
    ds30c4.attachPress([](Vietduino_Task * me){
        feeder.stop();
        Serial.println(F("Stop FEEDER"));
    });

    ds30c4.attachRelease([](Vietduino_Task * me){
        feeder.write(4000);
        Serial.println(F("Start FEEDER"));
    });

    OTA_AccessPoint_Init();
}

void loop()
{
    VIETDUINO_UPDATE;
}