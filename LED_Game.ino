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

char redLights = 0b00000000;
char blueLights = 0b00000000;

void writePointLEDs(int redPoints, int bluePoints){
  digitalWrite(latchClock, LOW);
  shiftOut(serialData, shiftClock, MSBFIRST, bluePoints); //blue
  shiftOut(serialData, shiftClock, MSBFIRST, redPoints); //red
  digitalWrite(latchClock, HIGH);
}

void moveLeft(int steps, bool color, bool level){
  char mask;
  if(level){mask = 0b10101010;} //top
  else {mask = 0b01010101;} //bottom

  if(color){} //blue
  else {} //red
  
}

void getButtons() {
  RTLState = digitalRead(redTL);
  RTRState = digitalRead(redTR);
  RBLState = digitalRead(redBL);
  RBRState = digitalRead(redBR);
  BTLState = digitalRead(blueTL);
  BTRState = digitalRead(blueTR);
  BBLState = digitalRead(blueBL);
  BBRState = digitalRead(blueBR);
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

void setTarget() {

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
  testButtons();
  writePointLEDs(redLights, blueLights);
}
