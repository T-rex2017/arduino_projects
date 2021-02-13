#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal_I2C.h>
#include "MAX30100.h"
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial BTserial(2, 3); // RX | TX

#define REPORTING_PERIOD_MS     1000

MAX30100 sensor;
PulseOximeter pox;

uint32_t tsLastReport = 0;
uint32_t tsTempSampStart;

bool debug = false;

void onBeatDetected()
{
  if (debug == true) Serial.println("Beat!");
}

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

void setup()
{
  if (debug == true)  Serial.begin(115200);
  lcd.begin();
  BTserial.begin(9600);
  if (debug == true)  Serial.print("Initializing pulse oximeter.."); \

  lcd.createChar(0, tempChar);

  lcd.setCursor(0, 0);
  lcd.print("Heart Beat SPO2");
  lcd.setCursor(0, 1);
  lcd.print("And Temperature");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensing System");
  delay(1000);

  if (!pox.begin()) {
    if (debug == true) Serial.println("FAILED");
    for (;;);
  } else {
    if (debug == true)  Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    startTemp();
    float bpm = pox.getHeartRate();
    int spo2 = pox.getSpO2();
    float temp = sensor.retrieveTemperature();
    tsLastReport = millis();

    if (spo2 >= 99) spo2 = 99;

    if (debug == true) {
      Serial.print("Heart rate:");
      Serial.print(bpm);
      Serial.print(" SpO2:");
      Serial.print(spo2);
      Serial.print("%");
      Serial.print(" Temp : ");
      Serial.print(temp);
      Serial.println("C");
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(bpm);
    lcd.print("BPM");
    lcd.print(" ");
    lcd.print(spo2);
    lcd.print("%");
    lcd.print("SPO2");
    lcd.setCursor(0, 1);
    lcd.print(temp);
    lcd.write(0);
    lcd.print("C");

    BTserial.print("BPM : ");
    BTserial.print(bpm);
    BTserial.print(" SPO2 : ");
    BTserial.print(spo2);
    BTserial.print(" Temp : ");
    BTserial.print(temp);
    BTserial.println("*C");
  }
}

void startTemp() {
  tsTempSampStart = millis();
  sensor.startTemperatureSampling();
  while (!sensor.isTemperatureReady()) {
    if (millis() - tsTempSampStart > 1000) {
      if (debug == true)  Serial.println("ERROR: timeout");
      // Stop here
      for (;;);
    }
  }
}
