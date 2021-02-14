#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

char *typeName[] = {"Object", "Ambient"};
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int pos = 0;
int buzPin = 8;
bool doorState;
bool highTemp;

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

void setup() {
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, tempChar);

  myservo.attach(9);

  pinMode(buzPin, OUTPUT);

  mlx.begin();
}

void loop() {
  float tempC = mlx.readObjectTempC();
  float tempF = mlx.readObjectTempF();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DoorState ");
  if (doorState == HIGH && highTemp == false) lcd.print("Open");
  else if (doorState == LOW && highTemp == false) lcd.print("Closed");
  else if (highTemp == true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Warning HighTemp");
  }
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.write(0);
  lcd.print("C ");
  lcd.print(tempF);
  lcd.write(0);
  lcd.print("F");

  if (tempC < 30.00) {
    myservo.write(90);
    delay(1000);
    doorState = LOW;
    highTemp = false;
  }
  else if ( tempC > 30.00 && tempC < 34.50 ) {
    myservo.write(10);
    delay(1000);
    doorState = HIGH;
    highTemp = false;
  }
  else if ( tempC >= 34.50) {
    digitalWrite(buzPin, HIGH);
    delay(100);
    digitalWrite(buzPin, LOW);
    delay(100);
    doorState = LOW;
    highTemp = true;
  }
}
