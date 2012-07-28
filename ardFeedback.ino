const int BLINKING_TIME = 175;

boolean blinking = false;
int lastblinkingcolor = 2;
int direction = 1;

void initLedPins() {
  for (int thisPin = 2; thisPin < 10; thisPin++) {
    pinMode(thisPin, OUTPUT);
  } 
}

void setup() {
  Serial.begin(9600); 
  initLedPins();
  blinking = false;
}

void alllightoff() {
  for (int thisPin = 2; thisPin < 10; thisPin++) {
    digitalWrite(thisPin, LOW);
  }
}

void lighton(int color) {
  switch (color) {
  case 'G':    
    alllightoff();
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    break;
  case 'Y':    
    alllightoff();
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);      
    break;
  case 'R':    
    alllightoff();
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);      
    break;
  case 'B' :
    blinking = true;
    blink();
    break;
  default:
    alllightoff();

  }

}

void blink() {
  int next;

  if ((direction == 1) && (lastblinkingcolor == 9)) {
    direction = -1;
  } 

  if ((direction == -1) && (lastblinkingcolor == 2)) {
    direction = 1;
  } 

  next = lastblinkingcolor + direction;

  alllightoff();

  digitalWrite(next, HIGH);
  delay(BLINKING_TIME);  
  lastblinkingcolor = next;

}

void loop() {

  if (Serial.available() > 0) {
    blinking = false;
    int inByte = Serial.read();
    lighton(inByte);
  } 
  else {
    if (blinking) {
      blink();
    }
  }
}


