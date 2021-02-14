#include <RH_ASK.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

RH_ASK driver;

int fanPin = 6;
int fanSpeed;
bool debug = false;
int newVal;
int oldVal;

void setup()
{
  if (debug == true) Serial.begin(9600);
  if (!driver.init()) {
    if (debug == true)  Serial.println("init failed");
  }
  lcd.begin();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("RF Based 4 Mode");
  lcd.setCursor(0, 1);
  lcd.print("FanSpeed Control");
  delay(2000);
  
  pinMode(fanPin, OUTPUT);
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) {
    newVal = buf[0];
    if (oldVal != newVal){
      lcd.clear();
      oldVal = newVal;
    }
    //if (debug == true) Serial.println(buf[0]);
    if (buf[0] == 48) {
      analogWrite(fanPin, 0);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed Mode : 0");
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed : 0%");
      if (debug == true) Serial.println(0);
    }
    else if (buf[0] == 49) {
      analogWrite(fanPin, 64);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed Mode : 1");
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed : 25%");
      if (debug == true) Serial.println(64);
    }
    else if (buf[0] == 50) {
      analogWrite(fanPin, 127);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed Mode : 2");
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed : 50%");
      if (debug == true) Serial.println(127);
    }
    else if (buf[0] == 51) {
      analogWrite(fanPin, 191);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed Mode : 3");
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed : 75%");
      if (debug == true) Serial.println(191);
    }
    else if (buf[0] == 52) {
      analogWrite(fanPin, 255);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed Mode : 4");
      lcd.setCursor(0, 1);
      lcd.print("Fan Speed : 100%");
      if (debug == true) Serial.println(255);
    }
  }
}
