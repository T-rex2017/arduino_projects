#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

bool debug = true;

int s1 = 2;
int s2 = 3;
int s3 = 4;
int s4 = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(s1, INPUT_PULLUP);
  pinMode(s2, INPUT_PULLUP);
  pinMode(s3, INPUT_PULLUP);
  pinMode(s4, INPUT_PULLUP);

  if (!driver.init())
    Serial.println("init failed");
}
void sends(const char *a) {
  driver.send((uint8_t *)a, strlen(a));
  driver.waitPacketSent();
  if (debug == true) Serial.println(a);
}

void loop() {
  bool s1s = digitalRead(s1);
  bool s2s = digitalRead(s2);
  bool s3s = digitalRead(s3);
  bool s4s = digitalRead(s4);

  if (s1s == false && s2s == true && s3s == true && s4s == true) {
    sends("1");
  }
  else if (s1s == false && s2s == false && s3s == true && s4s == true) {
    sends("2");
  }
  else if (s1s == false && s2s == false && s3s == false && s4s == true) {
    sends("3");
  }
  else if (s1s == false && s2s == false && s3s == false && s4s == false) {
    sends("4");
  }
  else {
    sends("0");
  }
}
