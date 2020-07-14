#include <SoftwareSerial.h>
#include "DHT.h"

int tempPin = 2;
int TouchPin=8;
int ledPin=13;
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(tempPin, DHTTYPE);

void setup() {
    pinMode(TouchPin, INPUT);
    pinMode(ledPin,OUTPUT);
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    float temp = dht.readTemperature();
    int sensorValue = digitalRead(TouchPin);
    if(sensorValue==1)
    {
        digitalWrite(ledPin,HIGH);
        Serial.println("Now Temperture is: ");
        Serial.println(temp);
    }
    else
    {
        digitalWrite(ledPin,LOW);
    }
    delay(200);
    
}
