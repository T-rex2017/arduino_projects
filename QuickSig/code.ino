int led[] = {2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, A5, A4}; // led pins
int sensor[] = {A0, A1, A2, A3}; //sensor pins

int redDelay = 5000;
int yellowDelay = 2000;
String finalint = "0000";
int ondelay = 300;
bool needDelay = false;

void setup() {
  for (int i = 0; i < 12; i++) {
    pinMode(led[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(sensor[i], INPUT);
  }
  
 /*
 below code is the animation on startup in which all leds one by one are turned on and then turned of
 */
  for (int i = 0; i < 12; i++){
    digitalWrite(led[i], HIGH);
    delay(ondelay);
    digitalWrite(led[i], LOW);
  }
}

/*
below function will pull all led's to LOW state
*/

void clearleds(){
  for (int i = 0; i < 12; i++) {
    digitalWrite(led[i], LOW);
  }
}
/*
lane 0 - lan3 are the function which light up the green led of the specified line and red led on all other lanes
if needDelay is true then after a time delay the green led on specified lane turns of and signal switches to orange 
this is used when 2 or more sensors give HIGH signal at the same time, blloen ne3edDleay is used to 
allow/denay the switching to ornage led
*/
void lane0(bool needDelay) {
  if (needDelay != true){
    digitalWrite(led[0], HIGH);
    digitalWrite(led[2], LOW);
    digitalWrite(led[5], HIGH);
    digitalWrite(led[8], HIGH);
    digitalWrite(led[11], HIGH);
  }
  else {
    digitalWrite(led[0], HIGH);
    digitalWrite(led[2], LOW);
    digitalWrite(led[5], HIGH);
    digitalWrite(led[8], HIGH);
    digitalWrite(led[11], HIGH);
    delay(redDelay);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[0], LOW);
    delay(yellowDelay);
    digitalWrite(led[1], LOW);
  }
}

void lane1(bool needDelay) {
  if (needDelay != true){
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], HIGH);
    digitalWrite(led[5], LOW);
    digitalWrite(led[8], HIGH);
    digitalWrite(led[11], HIGH);
  }
  else{
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], HIGH);
    digitalWrite(led[5], LOW);
    digitalWrite(led[8], HIGH);
    digitalWrite(led[11], HIGH);
    delay(redDelay);
    digitalWrite(led[4], HIGH);
    digitalWrite(led[3], LOW);
    delay(yellowDelay);
    digitalWrite(led[4], LOW);
  }
}

void lane2(bool needDelay) {
  if (needDelay != true){
    digitalWrite(led[2], HIGH);
    digitalWrite(led[5], HIGH);
    digitalWrite(led[6], HIGH);
    digitalWrite(led[8], LOW);
    digitalWrite(led[11], HIGH);
  }
  else{
    digitalWrite(led[2], HIGH);
    digitalWrite(led[5], HIGH);
    digitalWrite(led[6], HIGH);
    digitalWrite(led[8], LOW);
    digitalWrite(led[11], HIGH);
    delay(redDelay);
    digitalWrite(led[7], HIGH);
    digitalWrite(led[6], LOW);
    delay(yellowDelay);
    digitalWrite(led[7], LOW);
  }
}

void lane3(bool needDelay) {
  if (needDelay != true){
    digitalWrite(led[2], HIGH);
    digitalWrite(led[5], HIGH);
    digitalWrite(led[8], HIGH);
    digitalWrite(led[9], HIGH);
    digitalWrite(led[11], LOW);
  }
  else {
    digitalWrite(led[2], HIGH);
    digitalWrite(led[5], HIGH);
    digitalWrite(led[8], HIGH);
    digitalWrite(led[9], HIGH);
    digitalWrite(led[11], LOW);
    delay(redDelay);
    digitalWrite(led[10], HIGH);
    digitalWrite(led[9], LOW);
    delay(yellowDelay);
    digitalWrite(led[10], LOW);
  }
}

void loop() {
  int int0 = digitalRead(sensor[0]);
  int int1 = digitalRead(sensor[1]);
  int int2 = digitalRead(sensor[2]);
  int int3 = digitalRead(sensor[3]);

  finalint = String(int0) + String(int1) + String(int2) + String(int3);
  /*
  all 4 sensors provide a HIGH (1) or LOW (0) based on the presence of an object infront of it 
  these 4 1/0 signals are added as a string to get a 4 digit number string , which is then compared with the possible values
  according to the digit produced the code under it is exicuted
  */
    
  if (finalint == "0000") {
    clearleds();
    /*
    code below is for the Orange blinking or standby mode
    */
    digitalWrite(led[1], HIGH);
    digitalWrite(led[4], HIGH);
    digitalWrite(led[7], HIGH);
    digitalWrite(led[10], HIGH);
    delay(500);
    digitalWrite(led[1], LOW);
    digitalWrite(led[4], LOW);
    digitalWrite(led[7], LOW);
    digitalWrite(led[10], LOW);
    delay(500);
  }
  else if (finalint == "1000") {
    clearleds();
    lane0(needDelay = false);
  }
  else if (finalint == "0100") {
    clearleds();
    lane1(needDelay = false);
  }
  else if (finalint == "0010") {
    clearleds();
    lane2(needDelay = false);
  }
  else if (finalint == "0001") {
    clearleds();
    lane3(needDelay = false);
  }
  else if (finalint == "0011") {
    clearleds();
    lane2(needDelay = true);
    lane3(needDelay = true);
  }
  else if (finalint == "1100") {
    clearleds();
    lane0(needDelay = true);
    lane1(needDelay = true);
  }
  else if (finalint == "0110") {
    clearleds();
    lane1(needDelay = true);
    lane2(needDelay = true);
  }
  else if (finalint == "1001") {
    clearleds();
    lane0(needDelay = true);
    lane3(needDelay = true);
  }
  else if (finalint == "0101") {
    clearleds();
    lane1(needDelay = true);
    lane3(needDelay = true);
  }
  else if (finalint == "1010") {
    clearleds();
    lane0(needDelay = true);
    lane2(needDelay = true);
  }
  else if (finalint == "1110") {
    clearleds();
    lane0(needDelay = true);
    lane1(needDelay = true);
    lane2(needDelay = true);
  }
  else if (finalint == "1101") {
    clearleds();
    lane0(needDelay = true);
    lane1(needDelay = true);
    lane3(needDelay = true);
  }
  else if (finalint == "1011") {
    clearleds();
    lane0(needDelay = true);
    lane2(needDelay = true);
    lane3(needDelay = true);
  }
  else if (finalint == "0111") {
    clearleds();
    lane1(needDelay = true);
    lane2(needDelay = true);
    lane3(needDelay = true);
  }
  else if (finalint == "1111") {
    clearleds();
    lane0(needDelay = true);
    lane1(needDelay = true);
    lane2(needDelay = true);
    lane3(needDelay = true);
  }
  else {
    ;
  } 
}
