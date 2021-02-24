#include <Servo.h> // including servo library.
#include <LiquidCrystal_I2C.h>  // includeing I2C lcd library.
#include <ESP8266WiFi.h>        // including NODEMCU library.
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "< >" //--> URL address of your Firebase Realtime Database.
#define FIREBASE_AUTH "< >" //--> Your firebase database secret code.

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router.

#define lcd_addr 0x27     // I2C address of typical I2C LCD Backpack.

// LCD Pins to I2C LCD Backpack - These are default for HD44780 LCD's.
#define Rs_pin 0
#define Rw_pin 1
#define En_pin 2
#define BACKLIGHT_PIN 3
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C i2c_lcd(lcd_addr,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

const char* ssid = "< >"; //--> Your wifi name or SSID.
const char* password = "< >"; //--> Your wifi password.
Servo entry_servo; // Giving name to entry_servo.
Servo exit_servo; // Giving name to exit_servo.

int entry_ir;
int exit_ir;
long randNumber;

void setup() {

  
  i2c_lcd.begin (16,2); //  our LCD is a 16x2, change for your LCD if needed.
  // LCD Backlight ON
  i2c_lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  i2c_lcd.setBacklight(HIGH); 
  i2c_lcd.clear(); // Clear the LCD screen.
  
  pinMode(14,INPUT);  //Attaching entry_IR to D5.
  pinMode(12,INPUT);  //Attaching exit_IR to D6.
  entry_servo.attach(13); // Attaching Servo to D7.
  exit_servo.attach(15); // Attaching Servo to D8
  Serial.begin(9600);
  delay(500);
  
  WiFi.begin(ssid, password); 
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH); 
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
    
  
  entry_ir = digitalRead(14);
  exit_ir = digitalRead(12);
  randNumber = 0;
  String dataSend = String(randNumber); 
  String getentry= Firebase.getString("project123/entrygate");
  String getexit= Firebase.getString("project123/exitgate");
  String RAILWAYSTATION= Firebase.getString("project123/RAILWAY STATION");

  i2c_lcd.setCursor(4,0);
  i2c_lcd.print("WELCOME");
  i2c_lcd.setCursor(0,1);
  i2c_lcd.print("Total=4");
  i2c_lcd.setCursor(8,1);
  i2c_lcd.print("Empty=");
  i2c_lcd.setCursor(15,1);
  i2c_lcd.print(RAILWAYSTATION);
      
  if (Firebase.failed()) { 
      Serial.print("Getting /Value failed :");
      Serial.println(Firebase.error()); 
      delay(500); 
      return;
  }
  
 if (getentry == "1" && entry_ir==0){                        // "getentry" will be equal to 1 when the user enter the correct otp for entry gate in the Proparking app. "entry_ir" will be equal to 1 when vehicle is deteted by ir at entry gate.
  entry_servo.write(0);Serial.println("entry_gate open");
  delay(3000);
  entry_servo.write(90);Serial.println("entry_gate close");   // after 3 seconds the gate is closed.

  Firebase.setString("project123/entrygate",dataSend);
   
   if (Firebase.failed()) { 
      Serial.print("Setting /Value failed :");
      Serial.println(Firebase.error());  
      delay(500);
      return;
  }
 }
 
  if (getexit == "1" && exit_ir==0){                         // "getexit" will be equal to 1 when the user enter the correct otp for exit gate in the Proparking app. "exit_ir" will be equal to 1 when vehicle is deteted by ir at exit gate
  exit_servo.write(0);Serial.println("exit_gate open");
  delay(3000);
  exit_servo.write(90);Serial.println("exit_gate close");     // after 3 seconds the gate is closed.

  Firebase.setString("project123/exitgate",dataSend);
   
   if (Firebase.failed()) { 
      Serial.print("Setting /Value failed :");
      Serial.println(Firebase.error());  
      delay(500);
      return;
  }
 }
}
