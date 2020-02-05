#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#include "LiquidCrystal_I2C.h"

#define SD_ChipSelectPin 4
TMRpcm music;

LiquidCrystal_I2C lcd(0x27, 16, 2);

char j=0,x;
char Card_No[13];
char rfid1[13]="720051D5DA2C";
char rfid2[13]="6B0029EC9739";
char rfid3[13]="6B0029C153D0";

// jayesh lexmi

void setup() 
{
  Serial.begin(9600);
  music.speakerPin = 9; //Auido out on pin 9
  SD.begin(SD_ChipSelectPin);
  music.setVolume(5);    // Set volume level
  music.quality(1);        //  Set 1 for 2x oversampling Set 0 for normal
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Automatic  Bus ");
  lcd.setCursor(0, 1);
  lcd.print("AnnouncingSystem");

}
 
void loop() 
{ 
  if (Serial.available()>0) 
  {
    x=Serial.read();          
    Card_No[j] =x;
    j++;
    if(j==12)
    {  
      Card_No[j]='\0';
      j=0;
      if(!strcmp(rfid1,Card_No))
      {
        music.play("Kondody.wav"); // audio 1
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Kondody Bus");
        lcd.setCursor(0, 1);
        lcd.print("KTM - KPLY");
        delay(3000);
      }
      else if(!strcmp(rfid2,Card_No))
      {
        music.play("Jayesh.wav"); // audio 2
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Jayesh Bus");
        lcd.setCursor(0, 1);
        lcd.print("KTM - EKLM");
        delay(3000);
      }
      else if(!strcmp(rfid3,Card_No))
      {
        music.play("Lexmi.wav"); // audio 3
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Lexmi Bus");
        lcd.setCursor(0, 1);
        lcd.print("KTM - KLM");
        delay(3000);
      }
      else
      {  
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("CardID not found");
        lcd.setCursor(0, 1);
        lcd.print("Contact Office");
        delay(3000);
      }
    }  
  }
}
