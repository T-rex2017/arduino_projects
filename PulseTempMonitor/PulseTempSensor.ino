#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3); // RX | TX

#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const int PulseWire = A1;
const int LED13 = 13;
int Threshold = 550;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

PulseSensorPlayground pulseSensor;

byte tempChar[] = {
  B00110,
  B01001,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000
};
byte heartChar[] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,
  B00000,
  B00000
};

void setup() {

  Serial.begin(9600);
  BTserial.begin(9600);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold);

  dht.begin();

  lcd.begin();

  lcd.createChar(0, tempChar);
  lcd.createChar(1, heartChar);

  lcd.setCursor(0, 0);
  lcd.print("Heart Beat And");
  lcd.setCursor(0, 1);
  lcd.print("Temperature");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensing System");

  if (pulseSensor.begin()) {
    // Serial.println("We created a pulseSensor Object !");
  }
}

void loop() {

  delay(10);
 
  int myBPM = pulseSensor.getBeatsPerMinute();
  float myTEMP = dht.readTemperature();

  Serial.print("BPM : ");
  Serial.print(myBPM);
  Serial.print(" TEMP : ");
  Serial.println(myTEMP);

  BTserial.print("BPM : ");
  BTserial.print(myBPM);
  BTserial.print(" TEMP : ");
  BTserial.println(myTEMP);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BPM");
  lcd.write(1);
  lcd.print(" : ");
  lcd.print(myBPM);
  lcd.setCursor(0, 1);
  lcd.print("Temp : ");
  lcd.print(myTEMP);
  lcd.write(0);
  lcd.print("C");
}
