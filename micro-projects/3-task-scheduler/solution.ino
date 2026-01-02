// ========================================
// # 3. Software task scheduler
// 
// * Run LED blink, LED brightness change, and buzzer tick at different intervals
// * No `delay()`*
// ========================================

// Obvious Values
#define BRIGHTNESS_MAX 255
#define BRIGHTNESS_MIN 0

// Pin nums for 2 pwm LEDs
#define PWM_LED0 3
#define PWM_LED1 5

// Pin nums for 3 normal LEDs
#define LED0 7
#define LED1 8
#define LED2 12

// Pin for Buzzer
#define BUZZER 13

// the 2 LEDs that change brightness
const int NUM_PWM_LEDS = 2;
const int pwmLedPins[NUM_PWM_LEDS] = { PWM_LED0, PWM_LED1 };
unsigned long pwmPreviousMillis[NUM_PWM_LEDS] = { 0, 0 };
const long pwmIntervals[NUM_PWM_LEDS] = { 50, 100 };
const int brightnessInterval[NUM_PWM_LEDS] = { 1, 10 };
int pwmLedStates[NUM_PWM_LEDS] = { 0, 0 };
bool hasReachedMax[NUM_PWM_LEDS] = { false, false };

// the 3 LEDs
const int NUM_LEDS = 3;
const int ledPins[NUM_LEDS] = { LED0, LED1, LED2 };
unsigned long previousMillis[NUM_LEDS] = { 0, 0, 0 };
const long intervals[NUM_LEDS] = { 1000, 2000, 3000 };
int ledStates[NUM_LEDS] = { LOW, LOW, LOW };

// Buzzer
unsigned long buzzerPreviousMillis = 0;
const long buzzerInterval = 3000;
int buzzerState = LOW;

void setup() {
  for (int i = 0; i < NUM_PWM_LEDS; i++) {
    pinMode(pwmLedPins[i], OUTPUT);
    analogWrite(pwmLedPins[i], pwmLedStates[i]);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    analogWrite(ledPins[i], ledStates[i]);
  }
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, buzzerState);
}

void changeBrightnessOf(int index, bool increasing);
void loop() {
  unsigned long currentMillis = millis();

  // The 2 LEDs that are PWM (meaning they can change brightness)
  for (int i = 0; i < NUM_PWM_LEDS; i++) {
    if (currentMillis - pwmPreviousMillis[i] >= pwmIntervals[i]) {
      pwmPreviousMillis[i] = currentMillis;
      
      changeBrightnessOf(i, !hasReachedMax[i]);
  
      analogWrite(pwmLedPins[i], pwmLedStates[i]);
    }
  }

  // The 3 LEDs that aren't PWM
  for (int i = 0; i < NUM_LEDS; i++) {
    if (currentMillis - previousMillis[i] >= intervals[i]) {
      previousMillis[i] = currentMillis;

      if (ledStates[i] == LOW) ledStates[i] = HIGH;
      else ledStates[i] = LOW;

      digitalWrite(ledPins[i], ledStates[i]);
    }
  }

  // Buzzer
  if (currentMillis - buzzerPreviousMillis >= buzzerInterval) {
    buzzerPreviousMillis = currentMillis;

    if (buzzerState == LOW) buzzerState = HIGH;
    else buzzerState = LOW;
  
    digitalWrite(BUZZER, buzzerState);
  }
}

void changeBrightnessOf(int index, bool increasing) {
  int nextVal = 0;
  if (increasing) {
    nextVal = pwmLedStates[index] + brightnessInterval[index];
    if (nextVal > BRIGHTNESS_MAX) {
      nextVal = nextVal - (brightnessInterval[index] * 2);
      hasReachedMax[index] = true;
    }
  }
  else {
    nextVal = pwmLedStates[index] - brightnessInterval[index];
    if (nextVal < BRIGHTNESS_MIN) {
      nextVal = nextVal + (brightnessInterval[index] * 2);
      hasReachedMax[index] = false;
    }
  }
  pwmLedStates[index] = nextVal;
}