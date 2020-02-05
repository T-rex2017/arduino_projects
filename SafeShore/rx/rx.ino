#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;
int btn = 2;
int led = 3;
int buz = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen))
  {
    //driver.printBuffer("Got:", buf, buflen);
    if (buf[0] == 104) {
      Serial.print("got : ");
      Serial.write(buf, buflen);
      Serial.println();
      if (digitalRead(btn) == LOW) {
        digitalWrite(led, HIGH);
        tone(buz, 1000);
        delay(500);
        digitalWrite(led, LOW);
        noTone(buz);
        delay(500);
      }
    }
  }
}
