#include "Vietduino_Manager_Priority.h"
#include "Vietduino_Led.h"
#include "Vietduino_Button.h"
#include "PinVar.h"

Vietduino_Led feeder(PIN_FEEDER, SIG_ACTIVE_FEEDER);
Vietduino_Button ds30c4;

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
        feeder.write(2000);
        Serial.println(F("Start FEEDER"));
    });
}

void loop()
{
    VIETDUINO_UPDATE;
}