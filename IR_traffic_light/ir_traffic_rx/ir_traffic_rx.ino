#include <IRremote.h>

int signal1[] = {A5, A4, A3};
int signal2[] = {2, 3, 4};
int signal3[] = {7, 8, 9};
int signal4[] = {A2, A1, A0};

int gDelay = 2000;
int yDelay = 500;
int ehold = 10000;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 3; i++) {
    pinMode(signal1[i], OUTPUT);
    pinMode(signal2[i], OUTPUT);
    pinMode(signal3[i], OUTPUT);
    pinMode(signal4[i], OUTPUT);
  }

  IrReceiver.begin(11, DISABLE_LED_FEEDBACK);

  digitalWrite(signal1[0] , HIGH);
  digitalWrite(signal2[2] , HIGH);
  digitalWrite(signal3[2] , HIGH);
  digitalWrite(signal4[2] , HIGH);
}

void loop() {
  normal(signal1);
  check_ir();
  normal(signal2);
  check_ir();
  normal(signal3);
  check_ir();
  normal(signal4);
  check_ir();
}

void check_ir() {
  Serial.println("we are at ir check");
  if (IrReceiver.decode()) {
    //IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();

    if (IrReceiver.decodedIRData.address == 0x0102) {
      if (IrReceiver.decodedIRData.command == 0x30) Serial.println("got 0x30");
      else if (IrReceiver.decodedIRData.command == 0x31) {
        Serial.println("got 0x31");
        hold_sig1();
      }
      else if (IrReceiver.decodedIRData.command == 0x32) { 
        Serial.println("got 0x32");
        hold_sig2();
      }
      else if (IrReceiver.decodedIRData.command == 0x33) {
        Serial.println("got 0x33");
        hold_sig3();
      }
      else if (IrReceiver.decodedIRData.command == 0x34) {
        Serial.println("got 0x34");
        hold_sig4();
      }
    }
  }
  delay(100);
}

void hold_sig1() {
  all_low();
  digitalWrite(signal1[0] , HIGH);
  digitalWrite(signal2[2] , HIGH);
  digitalWrite(signal3[2] , HIGH);
  digitalWrite(signal4[2] , HIGH);
  delay(ehold);\
  all_red();
  Serial.println("sig1 hold over .....");
}

void hold_sig2() {
  all_low();
  digitalWrite(signal1[2] , HIGH);
  digitalWrite(signal2[0] , HIGH);
  digitalWrite(signal3[2] , HIGH);
  digitalWrite(signal4[2] , HIGH);
  delay(ehold);
  all_red();
  Serial.println("sig2 hold over .....");
}

void hold_sig3() {
  all_low();
  digitalWrite(signal1[2] , HIGH);
  digitalWrite(signal2[2] , HIGH);
  digitalWrite(signal3[0] , HIGH);
  digitalWrite(signal4[2] , HIGH);
  delay(ehold);
  all_red();
  Serial.println("sig3 hold over .....");
}

void hold_sig4() {
  all_low();
  digitalWrite(signal1[2] , HIGH);
  digitalWrite(signal2[2] , HIGH);
  digitalWrite(signal3[2] , HIGH);
  digitalWrite(signal4[0] , HIGH);
  delay(ehold);
  all_red();
  Serial.println("sig4 hold over .....");
}

void all_red() {
  all_low();
  digitalWrite(signal1[2] , HIGH);
  digitalWrite(signal2[2] , HIGH);
  digitalWrite(signal3[2] , HIGH);
  digitalWrite(signal4[2] , HIGH);
}

void all_low() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(signal1[i], LOW);
    digitalWrite(signal2[i], LOW);
    digitalWrite(signal3[i], LOW);
    digitalWrite(signal4[i], LOW);
  }
}


void normal(int a[]) {
  Serial.println("doing normal loop");
  digitalWrite(a[0], HIGH);
  digitalWrite(a[1], LOW);
  digitalWrite(a[2], LOW);
  delay(gDelay);
  digitalWrite(a[0], LOW);
  digitalWrite(a[1], HIGH);
  delay(yDelay);
  digitalWrite(a[1], LOW);
  digitalWrite(a[2], HIGH);
}
