// PINS
#define POTENTIOMETER A0
constexpr int BUTTON = 4;
constexpr int RED_CONTROL_LED = 2;
constexpr int BLUE_CONTROL_LED = 3;
constexpr int BLUE_LED = 7;
constexpr int YELLOW_LED = 8;
constexpr int RED_LED = 9;

// Potentiometer Values
const int VALUE_THRESHOLD = 10;
int values[VALUE_THRESHOLD] = { 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const int ON_THRESHOLD = 500;
const int OFF_THRESHOLD = 450;
const int FAILSAFE_THRESHOLD = 1015;  // Near 1023
bool potDisconnected = false;

// Button Values
unsigned long buttonPreviousMillis = 0;
unsigned long lastDebounce = 0;
bool interruptTraffic = false;

// Normal LED Values
constexpr int NUM_LEDS = 3;
const int ledPins[NUM_LEDS] = { BLUE_LED, YELLOW_LED, RED_LED };
int activatedLed = 0;
const unsigned long goDuration = 30000;
const unsigned long waitDuration = 5000;
const unsigned long stopDuration = 60000;
unsigned long ledPreviousMillis = 0;

// Control LED Values
constexpr int NUM_CONTROL_LEDS = 2;
const int controlLedPins[NUM_CONTROL_LEDS] = { BLUE_CONTROL_LED, RED_CONTROL_LED };
int activatedControlLed = 0;
bool goBack = false;

void setup() {
  pinMode(POTENTIOMETER, INPUT_PULLUP);
  pinMode(BUTTON, INPUT);
  for (int i = 0; i < NUM_CONTROL_LEDS; i++) {
    pinMode(controlLedPins[i], OUTPUT);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Initialize potentiometer's large list of values
  int initial = analogRead(POTENTIOMETER);
  for (int i = 0; i < VALUE_THRESHOLD; i++) {
    values[i] = initial;
  }
}

int getAvg(int numArrLen, int numArr[]);
void appendValue(int value);
void lightUpCurrentControlLed();
void lightUpLed();
bool isPotDisconnected();
void loop() {
  // Potentiometer & control led logic
  appendValue(analogRead(POTENTIOMETER));
  int stable = getAvg(VALUE_THRESHOLD, values);

  // Detect disconnection
  potDisconnected = isPotDisconnected();

  if (potDisconnected) {
    // FAIL-SAFE MODE
    activatedControlLed = 0;   // Force OFF (or choose behavior)
  } else {
    if (stable >= ON_THRESHOLD) {
        activatedControlLed = 1;
    } else if (stable <= OFF_THRESHOLD) {
        activatedControlLed = 0;
    }
  }
  lightUpCurrentControlLed();
  
  // Button logic
  int buttonState = digitalRead(BUTTON);
  unsigned long currentMillis = millis();
  if (buttonState == HIGH) {
    lastDebounce = currentMillis - buttonPreviousMillis;
  } else {
    buttonPreviousMillis = currentMillis;
    if (lastDebounce >= 100 && lastDebounce <= 400 && !interruptTraffic) {
      interruptTraffic = true;
      lastDebounce = 0;
    }
  }
  
  // LEDs logic
  if (activatedLed == 0 || activatedLed == 2) { // Blue & Red Led
    if (
      ((activatedLed == 0 && (currentMillis - ledPreviousMillis) >= goDuration) ||
      (activatedLed == 2 && (currentMillis - ledPreviousMillis) >= stopDuration)) &&
      !interruptTraffic
    ) {
      if (activatedLed == 0) activatedLed++;
      else activatedLed--;
      ledPreviousMillis = currentMillis;
    } else if (interruptTraffic) {
      ledPreviousMillis = currentMillis;
      activatedLed = 1;
    }
  } else { // Yellow Led
    if ((currentMillis - ledPreviousMillis) >= waitDuration) {
      if ((!interruptTraffic && goBack) || activatedControlLed == 0) {
        activatedLed--;
        goBack = false;
      } else {
        activatedLed++;
        goBack = true;
      }
      interruptTraffic = false;
      ledPreviousMillis = currentMillis;
    }
  }
  lightUpLed();
}

int getAvg(int numArrLen, int numArr[]) {
  long sum = 0;
  for (int i = 0; i < numArrLen; i++) {
    sum += numArr[i];
  }
  return sum / numArrLen;
}

void appendValue(int value) {
  for (int i = 0; i < VALUE_THRESHOLD - 1; i++) {
    values[i] = values[i + 1];
  }
  values[VALUE_THRESHOLD - 1] = value;
}

void lightUpCurrentControlLed() {
  for (int i = 0; i < NUM_CONTROL_LEDS; i++) {
    digitalWrite(controlLedPins[i], LOW);
  }
  digitalWrite(controlLedPins[activatedControlLed], HIGH);
}

void lightUpLed() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  digitalWrite(ledPins[activatedLed], HIGH);
}

bool isPotDisconnected() {
  for (int i = 0; i < VALUE_THRESHOLD; i++) {
    if (values[i] < FAILSAFE_THRESHOLD) {
      return false;
    }
  }
  return true;
}