#include <IRremote.h>

int btns[] = {0, 1, 2, 3};

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(btns[i], INPUT);
  }
  for (int i = 0; i < 5; i++) {
    digitalWrite(btns[i], HIGH);
  }
  IrSender.begin(false);
}

uint16_t sAddress = 0x0102;
uint8_t sCommand = 0x30;
uint8_t sRepeats = 0;

void loop() {
  if (digitalRead(0) == 0)IrSender.sendNEC(sAddress, 0x31, sRepeats);
  delay(100);
  if (digitalRead(1) == 0)IrSender.sendNEC(sAddress, 0x32, sRepeats);
  delay(100);
  if (digitalRead(2) == 0)IrSender.sendNEC(sAddress, 0x33, sRepeats);
  delay(100);
  if (digitalRead(3) == 0)IrSender.sendNEC(sAddress, 0x34, sRepeats);
  delay(100);
  IrSender.sendNEC(sAddress, 0x30, sRepeats);
  delay(100);
}
