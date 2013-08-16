const int successLedPins[] = {2, 3, 4};
const int nbSuccessLeds = 3;
const int unstableLedPins[] = {5, 6};
const int nbUnstableLeds = 2;
const int failedLedPins[] = {7, 8, 9};
const int nbFailedLeds = 3;

const int BLINKING_TIME = 175;

const int nbAllLeds = nbSuccessLeds + nbUnstableLeds + nbFailedLeds;
int allLedPins[nbAllLeds];

boolean blinking = false;
int lastblinkingcolor = 2;
int direction = 1;

void initLedPins() {

  for(int i = 0; i < nbSuccessLeds; i++) {
    allLedPins[i] = successLedPins[i];
  }
  for(int i = 0; i < nbUnstableLeds; i++) {
    allLedPins[i + nbSuccessLeds] = unstableLedPins[i];
  }
  for(int i = 0; i < nbFailedLeds; i++) {
    allLedPins[i + nbSuccessLeds + nbUnstableLeds] = failedLedPins[i];
  }

  for (int i=0; i < nbAllLeds; i++) {
    pinMode(allLedPins[i], OUTPUT);
  }  
}

void setup() {
  Serial.begin(9600); 
  initLedPins();
  blinking = false;
}

void alllightoff() {
  for (int i=0; i < nbAllLeds; i++) {
    operateLeds(allLedPins, nbAllLeds, LOW);
  }  
}

void operateLed(const int ledPin, int status) {
  digitalWrite(ledPin, status);
}

void operateLeds(const int ledPins[], const int nbLeds, int status) {
  for (int i=0; i < nbLeds; i++) {
    operateLed(ledPins[i], status);
  }  
}

void lightOnLeds(const int ledPins[], const int nbLeds) {
  operateLeds(ledPins, nbLeds, HIGH);
}

void lightOffLeds(const int ledPins[], const int nbLeds) {
  operateLeds(ledPins, nbLeds, LOW);
}

void lighton(int color) {
  switch (color) {

  case 'G':
  case 'S':
    alllightoff();
    lightOnLeds(successLedPins, nbSuccessLeds);
    break;
  case 'Y':
  case 'U':    
    alllightoff();
    lightOnLeds(unstableLedPins, nbUnstableLeds);
    break;
  case 'R':
  case 'F':    
    alllightoff();
    lightOnLeds(failedLedPins, nbFailedLeds);
    break;
  case 'B' :
    blinking = true;
    blink_all();
    break;
  default:
    alllightoff();
  }
}

void blink_all() {
  int next;

  if ((direction == 1) && (lastblinkingcolor == nbAllLeds - 1)) {
    direction = -1;
  } 

  if ((direction == -1) && (lastblinkingcolor == 0)) {
    direction = 1;
  } 

  next = lastblinkingcolor + direction;

  alllightoff();

  operateLed(allLedPins[next], HIGH);
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
      blink_all();
    }
  }
}
