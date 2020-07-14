#include <Wire.h>
#include <Servo.h>
#include <Bridge.h>

const int sensor1 = 8;
const int sensor5 = 9;
const int sensor10 = 10;
const int sensor50 = 11;
Servo myservo1;
Servo myservo5;
Servo myservo10;
Servo myservo50;

int count1 = 0;
int count5 = 0;
int count10 = 0;
int count50 = 0;
int coinout=0;

int val1,val5,val10,val50;

void setup() {
  
  Serial.begin(115200);
  Bridge.begin();  
  Serial1.begin(57600);
  Serial.setTimeout(5);

  pinMode(sensor1, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor10, INPUT);
  pinMode(sensor50, INPUT);
  myservo1.attach(4);
  myservo5.attach(5);
  myservo10.attach(6);
  myservo50.attach(7);
  myservo1.write(100);
  myservo5.write(100);
  myservo10.write(100);
  myservo50.write(80);

  delay(1000);
}

void coinupdate(){
  Serial.print("Coin"); 
  Serial.print("  $1:");
  Serial.print(count1);
  Serial.print(" $5:");
  Serial.print(count5); 
  Serial.print(" $10:");
  Serial.print(count10);
  Serial.print(" $50:");
  Serial.println(count50);
  Serial.print(" Total: ");
  Serial.println(count1*1+count5*5+count10*10+count50*50);

  Bridge.put("Coin_1", String(count1));
  Bridge.put("Coin_5", String(count5));
  Bridge.put("Coin_10", String(count10));
  Bridge.put("Coin_50", String(count50));
  Bridge.put("InformationOut", String("Working"));

}

void loop() {

   String tmp;
  
   val1 = digitalRead(sensor1);
   val5 = digitalRead(sensor5);
   val10 = digitalRead(sensor10);
   val50 = digitalRead(sensor50);
   tmp=Serial1.readString();
   coinout=tmp.toInt();

  if (val1 == LOW) {
    count1 ++;
    Serial.print("$1 ");
    Serial.println(count1);
    coinupdate();
    delay(250);
  }
  if (val5 == LOW) {
    count5 ++;
    Serial.print("$5 ");
    Serial.println(count5);
    coinupdate();
    delay(250);
  }
  if (val10 == LOW) {
    count10 ++;
    Serial.print("$10 ");
    Serial.println(count10);
    coinupdate();
    delay(250);
  }
    if (val50 == LOW) {
    count50 ++;
    Serial.print("$50 ");
    Serial.println(count50);
    coinupdate();
    delay(250);
  }

  if(coinout!=0 && coinout!=9999){
      int cout1=0;
      int cout5=0;
      int cout10=0;
      int cout50=0;
      int err=0;
      int value=0;
      Serial.println(coinout);
      while(50<=coinout && count50-cout50>=0){
        cout50++;
        coinout-=50;
      }
      while(10<=coinout && count10-cout10>=0){
        cout10++;
        coinout-=10;
      }
      while(5<=coinout && count5-cout5>=0){
        cout5++;
        coinout-=5;
      }
      while(1<=coinout && count1-cout1>=0){
        cout1++;
        coinout-=1;
      }
      if(cout1*1+cout5*5+cout10*10+cout50*50!=coinout){
        err=1;
      }
      
      
      Serial.print(" ");
      Serial.print(cout1);
      Serial.print(" ");
      Serial.print(cout5);
      Serial.print(" ");
      Serial.print(cout10);
      Serial.print(" ");
      Serial.println(cout50);
            
      for(int i=0;i<cout1;i++){
          myservo1.write(180);
          delay(1000);
          myservo1.write(100);
          delay(1000);
        }
        for(int i=0;i<cout5;i++){
          myservo5.write(180);
          delay(1000);
          myservo5.write(100);
          delay(1000);
        }
        for(int i=0;i<cout10;i++){
          myservo10.write(180);
          delay(1000);
          myservo10.write(100);
          delay(1000);
        }
        for(int i=0;i<cout50;i++){
          myservo50.write(170);
          delay(1000);
          myservo50.write(80);
          delay(1000);
        }
      if(err==0){
          Serial.println("No Error");
      }
      else if(err==1 && coinout!=0){
          Serial.println("Error");
      }
        myservo1.write(100);
        myservo5.write(100);
        myservo10.write(100);
        myservo50.write(80);
      
  }
  else if(coinout==9999){
      Serial.println("Reset");
      count1=0;
      count5=0;
      count10=0;
      count50=0;
      coinupdate();
  }
  
}
   


