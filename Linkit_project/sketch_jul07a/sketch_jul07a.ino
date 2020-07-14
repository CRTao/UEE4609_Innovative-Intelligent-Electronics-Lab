#include <Bridge.h>

int S1=0,S5=0,S10=2,S50=1;
String tt;

void setup() {
  Serial.begin(9600); // open internal serial connection to MT7688
  Bridge.begin();  
}

void loop() {  

  Serial.print(">>> ");
  Serial.print(S1);
  Serial.print(" ");
  Serial.print(S5);
  Serial.print(" ");
  Serial.print(S10);
  Serial.print(" ");
  Serial.println(S50);


  
  Bridge.put("Coin_1", String(S1));
  Bridge.put("Coin_5", String(S5));
  Bridge.put("Coin_10", String(S10));
  Bridge.put("Coin_50", String(S50));
  Bridge.put("InformationOut", String("Working"));

  delay(500);
}

