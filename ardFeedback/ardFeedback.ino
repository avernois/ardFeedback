const int SUCCESS = 0;
const int UNSTABLE = 1;
const int FAILED = 2;
const int ALL = 4;

const int pins[3][3] = {{2, 3, 4},
                    {5, 6, 0},
                    {7, 8, 9}};
const int nbLeds[3] = {3, 2, 3};

const int BLINKING_TIME = 175;

const int nbAllLeds = 9;
int allLedPins[nbAllLeds];

boolean blinking = false;
int lastblinkingcolor = 2;
int direction = 1;

int currentStatus;

void initLedPins() {

  for(int i = 0; i < nbLeds[SUCCESS]; i++) {
    allLedPins[i] = pins[SUCCESS][i];
  }
  for(int i = 0; i < nbLeds[UNSTABLE]; i++) {
    allLedPins[i + nbLeds[SUCCESS]] = pins[UNSTABLE][i];
  }
  for(int i = 0; i < nbLeds[FAILED]; i++) {
    allLedPins[i + nbLeds[SUCCESS] + nbLeds[UNSTABLE]] = pins[FAILED][i];
  }

  for (int i=0; i < nbAllLeds; i++) {
    pinMode(allLedPins[i], OUTPUT);
  }
}

void setup() {
  Serial.begin(9600); 
  initLedPins();
  stopBlinking();
}

void lightOffAllLeds() {
  for (int i=0; i < nbAllLeds; i++) {
    operateLeds(allLedPins, nbAllLeds, LOW);
  }  
}

void operateLed(const int ledPin, int level) {
  digitalWrite(ledPin, level);
}

void operateLeds(const int ledPins[], const int nbLeds, int level) {
  for (int i=0; i < nbLeds; i++) {
    operateLed(ledPins[i], level);
  }  
}

void lightOnLeds(const int status) {
  operateLeds(pins[status], nbLeds[status], HIGH);
}

void updateLeds(const int status) {
    stopBlinking();
    lightOffAllLeds();
    lightOnLeds(status);
}

void startBlinking(const int status) {
  blinking = true;
  blink(status);
}

void stopBlinking() {
  blinking = false;
}

void blink(const int status) {
   if (status == ALL) {
     blink_all();
   } else {
     lightOffAllLeds();
     delay(BLINKING_TIME*2);
     lightOnLeds(status);
     delay(BLINKING_TIME*2);
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

  lightOffAllLeds();

  operateLed(allLedPins[next], HIGH);
  delay(BLINKING_TIME);  
  lastblinkingcolor = next;
}

void lightOn(int color) {
  switch (color) {

  case 'G':
  case 'S':
    currentStatus = SUCCESS;
    updateLeds(currentStatus);
    break;
  case 'Y':
  case 'U':
    currentStatus = UNSTABLE;
    updateLeds(currentStatus);
    break;
  case 'R':
  case 'F':
    currentStatus = FAILED;
    updateLeds(currentStatus);
    break;
  case 'B' :
    currentStatus = ALL;
    startBlinking(currentStatus);
    break;
  case 'C' :
    startBlinking(currentStatus);
    break;
  default:
    lightOffAllLeds();
  }
}

void loop() {

  if (Serial.available() > 0) {
    int inByte = Serial.read();
    lightOn(inByte);
  } 
  else {
    if (blinking) {
      blink(currentStatus);
    }
  }
}
