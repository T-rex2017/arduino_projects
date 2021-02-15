#include "RTClib.h"
#include <DFPlayerMini_Fast.h>

RTC_DS3231 rtc;
int period = 0;
int myHour;
int myMinute;
int previousMinute;
bool debug = true;
int soundDelay = 1000;
int checkTimebtn = 2;
bool everyMinute = false;

int digi[] = {1, 2, 13, 24, 35, 46, 57, 58, 59, 60,
              3, 4, 5, 6, 7, 8, 9,
              10 , 11, 12, 14, 15, 16, 17, 18, 19,
              20, 21, 22, 23, 25, 26, 27, 28, 29,
              30, 31, 32, 33, 34, 36, 37, 38, 39,
              40, 41, 42, 42, 44, 45, 47, 48, 49,
              50, 51, 52, 53, 54, 55, 56, 62, 93
             };

#if !defined(UBRR1H)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
#endif

DFPlayerMini_Fast myMP3;

void setup() {
  Serial.begin(115200);
#if !defined(UBRR1H)
  mySerial.begin(9600);
  myMP3.begin(mySerial);
#else
  Serial1.begin(9600);
  myMP3.begin(Serial1);
#endif

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    if (debug == true)Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  pinMode(checkTimebtn, INPUT_PULLUP);

  myMP3.volume(30);
  delay(20);

  if (false) {
    myMP3.play(62);
  }
}

void loop() {
  DateTime now = rtc.now();
  myHour = now.hour();
  myMinute = now.minute();

  if (myHour > 12) {
    myHour = myHour - 12;
    period = 1;
  }
  if (myHour == 0) {
    period = 0;
  }
  if (previousMinute != myMinute && everyMinute == true) {
    previousMinute = myMinute;
    playSoundHour();
    delay(500);
    playSoundMinute();
    delay(500);
    playSoundPeriod();
    delay(3000);
  }

  if (digitalRead(checkTimebtn) == LOW) {
    playSoundHour();
    delay(500);
    playSoundMinute();
    delay(500);
    playSoundPeriod();
    delay(3000);
  }

  if (debug == true) {
    Serial.print(myHour);
    Serial.print(" : ");
    Serial.print(myMinute);
    Serial.println();

  }
}

void playSoundPeriod() {
  switch (period) {
    case 1:
      myMP3.play(digi[61]);
      break;
    case 2:
      myMP3.play(digi[62]);
      break;
  }
}

void playSoundHour() {
  switch (myHour) {
    case 0:
      myMP3.play(digi[0]);
      delay(soundDelay);
    case 1:
      myMP3.play(digi[1]);
      delay(soundDelay);
      break;
    case 2:
      myMP3.play(digi[2]);
      delay(soundDelay);
      break;
    case 3:
      myMP3.play(digi[3]);
      delay(soundDelay);
      break;
    case 4:
      myMP3.play(digi[4]);
      delay(soundDelay);
      break;
    case 5:
      myMP3.play(digi[5]);
      delay(soundDelay);
      break;
    case 6:
      myMP3.play(digi[6]);
      delay(soundDelay);
      break;
    case 7:
      myMP3.play(digi[7]);
      delay(soundDelay);
      break;
    case 8:
      myMP3.play(digi[8]);
      delay(soundDelay);
      break;
    case 9:
      myMP3.play(digi[9]);
      delay(soundDelay);
      break;
    case 10:
      myMP3.play(digi[10]);
      delay(soundDelay);
      break;
    case 11:
      myMP3.play(digi[11]);
      delay(soundDelay);
      break;
    case 12:
      myMP3.play(digi[12]);
      delay(soundDelay);
      break;
  }
}

void playSoundMinute() {
  switch (myMinute) {
    case 0:
      myMP3.play(digi[0]);
      delay(soundDelay);
      break;
    case 1:
      myMP3.play(digi[1]);
      delay(soundDelay);
      break;
    case 2:
      myMP3.play(digi[2]);
      delay(soundDelay);
      break;
    case 3:
      myMP3.play(digi[3]);
      delay(soundDelay);
      break;
    case 4:
      myMP3.play(digi[4]);
      delay(soundDelay);
      break;
    case 5:
      myMP3.play(digi[5]);
      delay(soundDelay);
      break;
    case 6:
      myMP3.play(digi[6]);
      delay(soundDelay);
      break;
    case 7:
      myMP3.play(digi[7]);
      delay(soundDelay);
      break;
    case 8:
      myMP3.play(digi[8]);
      delay(soundDelay);
      break;
    case 9:
      myMP3.play(digi[9]);
      delay(soundDelay);
      break;
    case 10:
      myMP3.play(digi[10]);
      delay(soundDelay);
      break;
    case 11:
      myMP3.play(digi[11]);
      delay(soundDelay);
      break;
    case 12:
      myMP3.play(digi[12]);
      delay(soundDelay);
      break;
    case 13:
      myMP3.play(digi[13]);
      delay(soundDelay);
      break;
    case 14:
      myMP3.play(digi[14]);
      delay(soundDelay);
      break;
    case 15:
      myMP3.play(digi[15]);
      delay(soundDelay);
      break;
    case 16:
      myMP3.play(digi[16]);
      delay(soundDelay);
      break;
    case 17:
      myMP3.play(digi[17]);
      delay(soundDelay);
      break;
    case 18:
      myMP3.play(digi[18]);
      delay(soundDelay);
      break;
    case 19:
      myMP3.play(digi[19]);
      delay(soundDelay);
      break;
    case 20:
      myMP3.play(digi[20]);
      delay(soundDelay);
      break;
    case 21:
      myMP3.play(digi[21]);
      delay(soundDelay);
      break;
    case 22:
      myMP3.play(digi[22]);
      delay(soundDelay);
      break;
    case 23:
      myMP3.play(digi[23]);
      delay(soundDelay);
      break;
    case 24:
      myMP3.play(digi[24]);
      delay(soundDelay);
      break;
    case 25:
      myMP3.play(digi[25]);
      delay(soundDelay);
      break;
    case 26:
      myMP3.play(digi[26]);
      delay(soundDelay);
      break;
    case 27:
      myMP3.play(digi[27]);
      delay(soundDelay);
      break;
    case 28:
      myMP3.play(digi[28]);
      delay(soundDelay);
      break;
    case 29:
      myMP3.play(digi[29]);
      delay(soundDelay);
      break;
    case 30:
      myMP3.play(digi[30]);
      delay(soundDelay);
      break;
    case 31:
      myMP3.play(digi[31]);
      delay(soundDelay);
      break;
    case 32:
      myMP3.play(digi[32]);
      delay(soundDelay);
      break;
    case 33:
      myMP3.play(digi[33]);
      delay(soundDelay);
      break;
    case 34:
      myMP3.play(digi[34]);
      delay(soundDelay);
      break;
    case 35:
      myMP3.play(digi[35]);
      delay(soundDelay);
      break;
    case 36:
      myMP3.play(digi[36]);
      delay(soundDelay);
      break;
    case 37:
      myMP3.play(digi[37]);
      delay(soundDelay);
      break;
    case 38:
      myMP3.play(digi[38]);
      delay(soundDelay);
      break;
    case 39:
      myMP3.play(digi[39]);
      delay(soundDelay);
      break;
    case 40:
      myMP3.play(digi[40]);
      delay(soundDelay);
      break;
    case 41:
      myMP3.play(digi[41]);
      delay(soundDelay);
      break;
    case 42:
      myMP3.play(digi[42]);
      delay(soundDelay);
      break;
    case 43:
      myMP3.play(digi[44]);
      delay(soundDelay);
      break;
    case 45:
      myMP3.play(digi[45]);
      delay(soundDelay);
      break;
    case 46:
      myMP3.play(digi[46]);
      delay(soundDelay);
      break;
    case 47:
      myMP3.play(digi[47]);
      delay(soundDelay);
      break;
    case 48:
      myMP3.play(digi[48]);
      delay(soundDelay);
      break;
    case 49:
      myMP3.play(digi[49]);
      delay(soundDelay);
      break;
    case 50:
      myMP3.play(digi[50]);
      delay(soundDelay);
      break;
    case 51:
      myMP3.play(digi[51]);
      delay(soundDelay);
      break;
    case 52:
      myMP3.play(digi[52]);
      delay(soundDelay);
      break;
    case 53:
      myMP3.play(digi[53]);
      delay(soundDelay);
      break;
    case 54:
      myMP3.play(digi[54]);
      delay(soundDelay);
      break;
    case 55:
      myMP3.play(digi[55]);
      delay(soundDelay);
      break;
    case 56:
      myMP3.play(digi[56]);
      delay(soundDelay);
      break;
    case 57:
      myMP3.play(digi[58]);
      delay(soundDelay);
      break;
    case 58:
      myMP3.play(digi[58]);
      delay(soundDelay);
      break;
    case 59:
      myMP3.play(digi[59]);
      delay(soundDelay);
      break;
  }
}

