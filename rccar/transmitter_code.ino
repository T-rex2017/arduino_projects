#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(10, 9); // CE, CSN

const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.

int frwd_btn = 3;
int back_btn = 8;
int left_btn = 2;
int ryte_btn = 7;

boolean frwd_btn_state = 0;
boolean back_btn_state = 0;
boolean left_btn_state = 0;
boolean ryte_btn_state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(frwd_btn, INPUT_PULLUP);
  pinMode(back_btn, INPUT_PULLUP);
  pinMode(left_btn, INPUT_PULLUP);
  pinMode(ryte_btn, INPUT_PULLUP);
  
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}
void loop()
{
  frwd_btn_state = digitalRead(frwd_btn);
  Serial.print("frwd_btn_state : ");
  Serial.print(frwd_btn_state);
  back_btn_state = digitalRead(back_btn);
  Serial.print(" back_btn_state : ");
  Serial.print(back_btn_state);
  left_btn_state = digitalRead(left_btn);
  Serial.print(" left_btn_state : ");
  Serial.print(left_btn_state);
  ryte_btn_state = digitalRead(ryte_btn);
  Serial.print(" ryte_btn_state : ");
  Serial.println(ryte_btn_state);
  
  if (frwd_btn_state == LOW)
  {
    //char text[] = "1000";
    int text = 1000;
    radio.write(&text, sizeof(text));                  //Sending the message to receiver
  }
  else if (back_btn_state == LOW)
  {
    int text = 0100;
    radio.write(&text, sizeof(text));                  //Sending the message to receiver
  }
  else if (left_btn_state == LOW)
  {
    int text = 0010;
    radio.write(&text, sizeof(text));                  //Sending the message to receiver
  }
  else if (ryte_btn_state == LOW)
  {
    int text = 0001;
    radio.write(&text, sizeof(text));                  //Sending the message to receiver
  }
  
  delay(100);
}
