#include <SoftwareSerial.h>
#include "DHT.h"

int tempPin = 2;
int TouchPin=8;
int ledPin=13;
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(tempPin, DHTTYPE);

int state=0,sec=10,w=0;
int count=0;

void setup() {
    pinMode(TouchPin, INPUT);
    pinMode(ledPin,OUTPUT);
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    float temp = dht.readTemperature();
    int sensorValue = digitalRead(TouchPin);
    if(state==0){
      if(sensorValue==1){sec+=2;Serial.println(sec);delay(500);}
      if(sensorValue==0){w++;delay(100);}
      
      
      if(temp>=25||w>20){
       state=1;
       Serial.print("Second to challenge : ");
       Serial.println(sec);
       Serial.println("Tap again to start,hold for the time !");
      }
      }
    
    if(state==1 && sensorValue==1){
    state=2;
    }
      
    if(state==2 && sensorValue==1)
    {
        digitalWrite(ledPin,HIGH);
        delay(1);
        count++;
    }
    if(state==2 && sensorValue==0){
    state=3;
    }
    if(state==3)
    {
        digitalWrite(ledPin,LOW);
        Serial.println("Challenge End.");
        Serial.print("Second to challenge : ");
        Serial.println(sec);
        Serial.print("Time you get: ");
        count/=4;
        Serial.println(count);
        Serial.println("Start over again automatically");
        state=0;
        count=0;
        sec=10;
        w=0;
        delay(2000);
    }
}
