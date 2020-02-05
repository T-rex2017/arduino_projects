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
  const char *msg = "hello";
  if (digitalRead(btn) == HIGH) {
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(led, HIGH);
    tone(buz, 1000);
    delay(500);
    digitalWrite(led, LOW);
    noTone(buz);
    delay(500);
    delay(200);
  }
}
