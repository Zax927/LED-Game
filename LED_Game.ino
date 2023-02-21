int clearPin = 0;
int serialData = 1;
int shiftClock = 2;
int latchClock = 3;

const int redTL = 4;
const int redTR = 5;
const int redBL = 6;
const int redBR = 7;
const int blueTL = 8;
const int blueTR = 9;
const int blueBL = 10;
const int blueBR = 11;

bool RTLState = LOW;
bool RTRState = LOW;
bool RBLState = LOW;
bool RBRState = LOW;
bool BTLState = LOW;
bool BTRState = LOW;
bool BBLState = LOW;
bool BBRState = LOW;

char redLights  = 0b00000011;
char blueLights = 0b00000011;

void writePointLEDs(int redPoints, int bluePoints){
  digitalWrite(latchClock, LOW);
  shiftOut(serialData, shiftClock, MSBFIRST, bluePoints); //blue
  shiftOut(serialData, shiftClock, MSBFIRST, redPoints); //red
  digitalWrite(latchClock, HIGH);
}

void getButtons(){
  RTLState = digitalRead(redTL);
  RTRState = digitalRead(redTR);
  RBLState = digitalRead(redBL);
  RBRState = digitalRead(redBR);
  BTLState = digitalRead(blueTL);
  BTRState = digitalRead(blueTR);
  BBLState = digitalRead(blueBL);
  BBRState = digitalRead(blueBR);
}

void moveLeft(int steps, bool color, bool level){
  char mask;
  char temp1;
  char temp2;
  if(level){mask = 0b10101010;} //top
  else {mask = 0b01010101;} //bottom

  if(color){ //blue
    temp1 = blueLights & mask; //mask off bits on other level
    temp1 = temp1 << (steps*2); //shift over
    temp2 = blueLights & (mask^0b11111111); //get bits from other level
    blueLights = temp1 | temp2; //combine shifted and other level
  } 
  else { //red
    temp1 = redLights & mask; //mask off bits on other level
    temp1 = temp1 << (steps*2); //shift over
    temp2 = redLights & (mask^0b11111111); //get bits from other level
    redLights = temp1 | temp2; //combine shifted and other level  
  }
}

void moveRight(int steps, bool color, bool level){
  char mask;
  char temp1;
  char temp2;
  if(level){mask = 0b10101010;} //top
  else {mask = 0b01010101;} //bottom

  if(color){ //blue
    temp1 = blueLights & mask; //mask off bits on other level
    temp1 = temp1 >> (steps*2); //shift over
    temp1 = temp1 & 0b00111111; //remove ones at beginning
    temp2 = blueLights & (mask^0b11111111); //get bits from other level
    blueLights = temp1 | temp2; //combine shifted and other level
  } 
  else { //red
    temp1 = redLights & mask; //mask off bits on other level
    temp1 = temp1 >> (steps*2); //shift over
    temp1 = temp1 & 0b00111111; //remove ones at beginning
    temp2 = redLights & (mask^0b11111111); //get bits from other level
    redLights = temp1 | temp2; //combine shifted and other level
  }
}

void moveLights(){
  if(BTLState){moveLeft(1,1,1); delay(200);}
  if(BTRState){moveRight(1,1,1); delay(200);}
  if(BBLState){moveLeft(1,1,0); delay(200);}
  if(BBRState){moveRight(1,1,0); delay(200);}

  if(RTLState){moveLeft(1,0,1); delay(200);}
  if(RTRState){moveRight(1,0,1); delay(200);}
  if(RBLState){moveLeft(1,0,0); delay(200);}
  if(RBRState){moveRight(1,0,0); delay(200);}
}

void testButtons() {
  if(RTLState){redLights = redLights | 0b10000000;} else {redLights = redLights & 0b01111111;}
  if(RTRState){redLights = redLights | 0b00100000;} else {redLights = redLights & 0b11011111;}
  if(RBLState){redLights = redLights | 0b00001000;} else {redLights = redLights & 0b11110111;}
  if(RBRState){redLights = redLights | 0b00000010;} else {redLights = redLights & 0b11111101;}

  if(BTLState){blueLights = blueLights | 0b10000000;} else {blueLights = blueLights & 0b01111111;}
  if(BTRState){blueLights = blueLights | 0b00100000;} else {blueLights = blueLights & 0b11011111;}
  if(BBLState){blueLights = blueLights | 0b00001000;} else {blueLights = blueLights & 0b11110111;}
  if(BBRState){blueLights = blueLights | 0b00000010;} else {blueLights = blueLights & 0b11111101;}
}

void setup() {
  pinMode(clearPin, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);
  pinMode(serialData, OUTPUT);

  pinMode(redTL, INPUT);
  pinMode(redTR, INPUT);
  pinMode(redBL, INPUT);
  pinMode(redBR, INPUT);
  pinMode(blueTL, INPUT);
  pinMode(blueTR, INPUT);
  pinMode(blueBL, INPUT);
  pinMode(blueBR, INPUT);



  digitalWrite(clearPin, LOW);
  digitalWrite(clearPin, HIGH);

  writePointLEDs(0, 0);
  delay(500);
}

void loop() {
  getButtons();
  //testButtons();
  moveLights();
  writePointLEDs(redLights, blueLights);
}
