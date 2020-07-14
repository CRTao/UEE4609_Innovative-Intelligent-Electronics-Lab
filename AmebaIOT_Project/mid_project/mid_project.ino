#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCM1602 I2C LCD
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const int sensor1 = 5;
const int sensor5 = 6;
const int sensor10 = 7;
const int sensor50 = 8;

int count1 = 0;
int count5 = 0;
int count10 = 0;
int count50 = 0;

void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor10, INPUT);
  pinMode(sensor50, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);               // initialize the lcd 
  lcd.backlight();
  
  lcd.setCursor ( 0, 0 );        // go to home
  lcd.print("Welcome!");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print ("Wait for coin.");
  delay(1000);

}

void coinupdate(){
  lcd.clear();
  lcd.setCursor ( 0, 0 );        // go to home
  lcd.print("Coin"); 
  lcd.print("  $1:");
  lcd.print(count1);
  lcd.print(" $5:");
  lcd.print(count5); 
  lcd.setCursor ( 0, 1 );        // go to the next line
  
  lcd.print(" $10:");
  lcd.print(count10);
  lcd.print(" $50:");
  lcd.print(count50);
  
}

void loop() {

  

  
  int val1 = digitalRead(sensor1);
  int val5 = digitalRead(sensor5);
  int val10 = digitalRead(sensor10);
  int val50 = digitalRead(sensor50);

  if (val1 == HIGH) {
    count1 ++;
    Serial.print("$1 ");
    Serial.println(count1);
    coinupdate();
    delay(100);
  }
  if (val5 == HIGH) {
    count5 ++;
    Serial.print("$5 ");
    Serial.println(count5);
    coinupdate();
    delay(100);
    
  }
  if (val10 == HIGH) {
    count10 ++;
    Serial.print("$10 ");
    Serial.println(count10);
    coinupdate();
    delay(100);
    
  }
    if (val50 == HIGH) {
    count50 ++;
    Serial.print("$50 ");
    Serial.println(count50);
    coinupdate();
    delay(100);
    
  }


}
