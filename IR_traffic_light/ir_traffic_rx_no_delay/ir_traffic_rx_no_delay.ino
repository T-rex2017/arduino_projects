#include <IRremote.h>

int signal1[] = {A5, A4, A3};
int signal2[] = {2, 3, 4};
int signal3[] = {7, 8, 9};
int signal4[] = {A2, A1, A0};

unsigned long previousMillis = 0;
long interval = 500;
long gdelay = 500;
long ydelay = 2000;
long holddelay = 15000;

int counter = 0;
int holdcounter = 0;

bool onhold = false;


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(signal1[i], OUTPUT);
    pinMode(signal2[i], OUTPUT);
    pinMode(signal3[i], OUTPUT);
    pinMode(signal4[i], OUTPUT);
  }

  IrReceiver.begin(11, DISABLE_LED_FEEDBACK);

  // digitalWrite(signal1[0] , HIGH);
  // digitalWrite(signal2[2] , HIGH);
  // digitalWrite(signal3[2] , HIGH);
  // digitalWrite(signal4[2] , HIGH);
}

void loop() {
  unsigned long currentMillis = millis();

  check_ir();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (holdcounter != 0 && onhold == true) holdcounter = 0;

    if (holdcounter == 0) {
      onhold = false;
    }
    else if (holdcounter == 1 && onhold != true) {
      // Serial.println("holding sig1");
      all_low();
      digitalWrite(signal1[0], HIGH);
      digitalWrite(signal2[2], HIGH);
      digitalWrite(signal3[2], HIGH);
      digitalWrite(signal4[2], HIGH);
      counter = 0;
      onhold = true;
      holdcounter = 0;
      interval = holddelay;
    }
    else if (holdcounter == 2 && onhold != true) {
      // Serial.println("holding sig2");
      all_low();
      digitalWrite(signal1[2], HIGH);
      digitalWrite(signal2[0], HIGH);
      digitalWrite(signal3[2], HIGH);
      digitalWrite(signal4[2], HIGH);
      counter = 0;
      onhold = true;
      holdcounter = 0;
      interval = holddelay;
    }
    else if (holdcounter == 3 && onhold != true) {
      // Serial.println("holding sig3");
      all_low();
      digitalWrite(signal1[2], HIGH);
      digitalWrite(signal2[2], HIGH);
      digitalWrite(signal3[0], HIGH);
      digitalWrite(signal4[2], HIGH);
      counter = 0;
      onhold = true;
      holdcounter = 0;
      interval = holddelay;
    }
    else if (holdcounter == 4 && onhold != true) {
      // Serial.println("holding sig4");
      all_low();
      digitalWrite(signal1[2], HIGH);
      digitalWrite(signal2[2], HIGH);
      digitalWrite(signal3[2], HIGH);
      digitalWrite(signal4[0], HIGH);
      counter = 0;
      onhold = true;
      holdcounter = 0;
      interval = holddelay;
    }

    if (onhold != true) {

      if (counter == 0) {
        //all_low();
        digitalWrite(signal4[1], LOW);
        digitalWrite(signal4[2], HIGH);
        digitalWrite(signal1[2], LOW);
        digitalWrite(signal1[0], HIGH);
        // for hold
        digitalWrite(signal2[2], HIGH);
        digitalWrite(signal3[2], HIGH);
        digitalWrite(signal4[2], HIGH);
        digitalWrite(signal2[0], LOW);
        digitalWrite(signal3[0], LOW);
        digitalWrite(signal4[0], LOW);
        counter++;
        interval = ydelay;
      }
      else if (counter == 1) {
        digitalWrite(signal1[0], LOW);
        digitalWrite(signal1[1], HIGH);
        counter++;
        interval = gdelay;
      }
      else if (counter == 2) {
        digitalWrite(signal1[1], LOW);
        digitalWrite(signal1[2], HIGH);
        digitalWrite(signal2[2], LOW);
        digitalWrite(signal2[0], HIGH);
        counter++;
        interval = ydelay;
      }
      else if (counter == 3) {
        digitalWrite(signal2[0], LOW);
        digitalWrite(signal2[1], HIGH);
        counter++;
        interval = gdelay;
      }
      else if (counter == 4) {
        digitalWrite(signal2[1], LOW);
        digitalWrite(signal2[2], HIGH);
        digitalWrite(signal3[2], LOW);
        digitalWrite(signal3[0], HIGH);
        counter++;
        interval = ydelay;
      }
      else if (counter == 5) {
        digitalWrite(signal3[0], LOW);
        digitalWrite(signal3[1], HIGH);
        counter++;
        interval = gdelay;
      }
      else if (counter == 6) {
        digitalWrite(signal3[1], LOW);
        digitalWrite(signal3[2], HIGH);
        digitalWrite(signal4[2], LOW);
        digitalWrite(signal4[0], HIGH);
        counter++;
        interval = ydelay;
      }
      else if (counter == 7) {
        digitalWrite(signal4[0], LOW);
        digitalWrite(signal4[1], HIGH);
        counter = 0;
        interval = gdelay;
      }
    }
  }
  delay(100);
}

void check_ir() {
  if (IrReceiver.decode()) {
    //IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();

    if (IrReceiver.decodedIRData.address == 0x0102) {
      if (IrReceiver.decodedIRData.command == 0x30) {
        // Serial.println("got 0x30");
        //holdcounter = 0;
      }
      else if (IrReceiver.decodedIRData.command == 0x31 && holdcounter != 1) {
        //Serial.println("got 0x31");
        holdcounter = 1;
      }
      else if (IrReceiver.decodedIRData.command == 0x32 && holdcounter != 2) {
        //Serial.println("got 0x32");
        holdcounter = 2;
      }
      else if (IrReceiver.decodedIRData.command == 0x33 && holdcounter != 3) {
        //Serial.println("got 0x33");
        holdcounter = 3;
      }
      else if (IrReceiver.decodedIRData.command == 0x34 && holdcounter != 4) {
        //Serial.println("got 0x34");
        holdcounter = 4;
      }
    }
  }
  // Serial.print(" hc in irc : ");
  // Serial.println(holdcounter);
}

void all_low() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(signal1[i], LOW);
    digitalWrite(signal2[i], LOW);
    digitalWrite(signal3[i], LOW);
    digitalWrite(signal4[i], LOW);
  }
}
