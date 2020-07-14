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

char ssid[] = "Tenda_421";      // your network SSID (name)
char pass[] = "87878787";   // your network password
int keyIndex = 0;  
int State = 0;
int button = 4;
int led = 13;
int status = WL_IDLE_STATUS;
int val1,val5,val10,val50;
int ini=0;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  lcd.begin(16,2);               // initialize the lcd 
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Opening...");
  
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
    delay(5000);
  }
  server.begin();
  pinMode(sensor1, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor10, INPUT);
  pinMode(sensor50, INPUT);

  lcd.clear();
  lcd.setCursor ( 0, 0 );        // go to home
  lcd.print("Welcome!");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print ("Wait for coin.");
  delay(1000);

  pinMode(button, INPUT_IRQ_RISE);
  digitalSetIrqHandler(button, button_handler);
  loop();
}

void button_handler(uint32_t id, uint32_t event) {

      State++;
      
      if (State==2)State=0;
      Serial.println(State);
        delay(100);
      digitalWrite(led,State);
      
      if(State==1){
        delay(50);
        showIP_LCD();
      }
      else{
        delay(50);
  lcd.clear();
  lcd.setCursor ( 0, 0 );        // go to home
  lcd.print("Welcome!");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print ("Wait for coin.");
      }
      delay(50);

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
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wifi Online.");
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
}

void loop() {
  
  if(State == 0){
      Serial.println("lol ");
   val1 = digitalRead(sensor1);
   val5 = digitalRead(sensor5);
   val10 = digitalRead(sensor10);
   val50 = digitalRead(sensor50);

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
    else
    {
      Serial.print("lmao 1");
   WiFiClient client = server.available();
   Serial.print("lmao 2");
  if (client) {
    Serial.print("lmao 3");
    Serial.println("new client");
    String currentLine = "";  
    while (client.connected()) {
      Serial.print("lmao #");
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
          // send a standard http response header
          
          //scancoin();
          
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();  
       
        client.print("<html>");
        client.print("<head>"); 
        client.print("<meta http-equiv=content-type content=text/html; charset=UTF-8>");     
        client.print("<meta http-equiv=\"Content-Language\" content=\"zh-tw\" />");  
        client.print("<style>"); 
        client.print("body,input{font-family: verdana, Times New Roman,微軟正黑體,新細明體;}");     
        client.print("p{text-align:center;font-size:35px;color:#202d82}");
        client.print("til{text-align:left;margin:25px;font-size:25px;}");
        client.print("table{text-align:center;border-collapse:collapse}");  
        client.print("und{align:right;margin:80px;padding:80px;font-size:20px}");      
        client.print("input{align:center;width:50px;height:50px;font-size:20px;}");
        client.print("td{width:2500px;align:center;margin:0px;padding:0px;font-size:25px}");     
        client.print("th{align:right;padding:20px;font-size:20px}");        
        client.print("</style>");      
        client.print("</head>");        
        client.print("<body bgcolor=#f9e6a2>");    
        client.print("<p><b>智慧零錢筒</b></p>");   
        client.print("<table border=0>");       
        client.print("<tr><td>一</td><td>五</td><td>十</td><td>五十</td></tr>");  
        client.print("<tr><td colspan=4><hr color=#ff8000></tr>");         
        client.print("<tr><td>"); 
        client.print("<form method=get><input type=hidden name=L1 value=1>"); 
        client.print("<input type=submit value=+></form></td>");       
        client.print("<td>");
        client.print("<form method=get><input type=hidden name=L2 value=1>"); 
        client.print("<input type=submit value=+></form></td>");
        client.print("<td>");
        client.print("<form method=get><input type=hidden name=L3 value=1>"); 
        client.print("<input type=submit value=+></form></td>"); 
        client.print("<td>");
        client.print("<form method=get><input type=hidden name=L4 value=1>"); 
        client.print("<input type=submit value=+></form></td>"); 
        client.print("</tr>");       
        client.print("<tr><th>");
        client.print(count1);
        client.print("</th><th>");
        client.print(count5);
        client.print("</th><th>"); 
        client.print(count10);
        client.print("</th><th>"); 
        client.print(count50);
        client.print("</th></tr>");    
        client.print("<tr>");
        client.print("<td>");
        client.print("<form method=get><input type=hidden name=L1 value=0>"); 
        client.print("<input type=submit value=-></form></td>");
        client.print("<td>");
        client.print("<form method=get><input type=hidden name=L2 value=0>"); 
        client.print("<input type=submit value=-></form></td>"); 
        client.print("<td>");
        client.print("<form method=get><input type=hidden name=L3 value=0>"); 
        client.print("<input type=submit value=-></form></td>"); 
        client.print("<td>");
        client.print("<form method=get><input type=hidden name=L4 value=0>"); 
        client.print("<input type=submit value=-></form></td>");
        client.print("</tr>");
        client.print("<tr><td colspan=4><hr color=#f9e6a2></tr>");
        client.print("<tr><td colspan=4>總計</td></tr>");
        client.print("<tr><td colspan=4><hr color=#ff8000></tr>");
        client.print("<tr><th colspan=4>");
        client.print(count1*1+count5*5+count10*10+count50*50);  
        client.print("</th></tr>"); 
        client.print("</table>");
        client.print("</body></html>"); 
        client.println();
        
        break;
        }
        else{
          // you're starting a new line
          currentLine = "";
        } 
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLine += c; 
        }
        if (currentLine.endsWith("L1=1")) count1++; 
        else if (currentLine.endsWith("L1=0")) count1--;
        else if (currentLine.endsWith("L2=1")) count5++; 
        else if (currentLine.endsWith("L2=0")) count5--;
        else if (currentLine.endsWith("L3=1")) count10++;                  
        else if (currentLine.endsWith("L3=0")) count10--;
        else if (currentLine.endsWith("L4=1")) count50++;
        else if (currentLine.endsWith("L4=0")) count50--;
        }
        
      }
        // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
  }


}
