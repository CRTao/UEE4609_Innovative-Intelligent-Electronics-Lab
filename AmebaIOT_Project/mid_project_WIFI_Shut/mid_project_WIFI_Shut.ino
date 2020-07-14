#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>


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

char ssid[] = "ssid";      // your network SSID (name)
char pass[] = "pass";   // your network password
int keyIndex = 0;  
int State = 0;

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();
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
  delay(3000);
  showIP_LCD();
  delay(5000);
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


void showIP_LCD()
{
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SSID:");
  lcd.print(WiFi.SSID());
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
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
  
    WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 15");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<H1>");
          // output the value of each analog input pin
           client.println(" <font size=\"7\" color=\"008800\">");
           client.print("Coin 1:");
            client.print(count1);
            client.print(" ");
            client.println("<br />");
           client.println(" <font size=\"7\" color=\"008800\">");
           client.print("Coin 5:");
            client.print(count5);
            client.print(" ");
            client.println("<br />");
           client.println(" <font size=\"7\" color=\"008800\">");
           client.print("Coin 10:");
            client.print(count10);
            client.print(" ");
            client.println("<br />");
            client.println(" <font size=\"7\" color=\"008800\">");
           client.print("Coin 50");
            client.print(count50);
            client.print(" ");
            client.println("<br />");
            client.println("</font>");
            client.println(" <font size=\"7\" color=\"ff0000\">");
            client.print("Total:");
            client.print(count1*1+count5*5+count10*10+count50*50);
            client.print(" ");
            client.println("<br />");
            client.println("</font>");
            client.println("</H1>");
            client.println("</html>");
            break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }


}
