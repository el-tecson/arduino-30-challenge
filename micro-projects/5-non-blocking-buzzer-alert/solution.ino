// PINS
constexpr int BUTTON = 2;
constexpr int BUZZER = 11;
constexpr int BUZZER_LED = 10;
constexpr int LED1 = 4;
constexpr int LED2 = 7;
constexpr int LED3 = 12;
constexpr int LED4 = 8;
constexpr int LED5 = 13;

// LED VALUES
constexpr int NUM_LEDS = 5;
const int ledPins[NUM_LEDS] = { LED1, LED2, LED3, LED4, LED5 };
unsigned long ledMillis = 0;
constexpr int ledThreshold = 100;
int curLed = 0;

// BUTTON DEBOUNCE VALUES
unsigned long previousMillis = 0;
unsigned long lastDebounce = 0;
unsigned long everSince = 0;
int curIndex = 0;
bool justPressed = false;
bool doubleClicked = false;
int buttonState = LOW;

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUZZER_LED, OUTPUT);
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void lightUp(int ledNum);
void loop() {
  // LED normal behaviour
  unsigned long currentMillis = millis();
  if (currentMillis - ledMillis >= ledThreshold) {
    ++curLed == NUM_LEDS ? (void)(curLed = 0) : (void)0;
    ledMillis = currentMillis;
  }
  lightUp(curLed);

  // Button & buzzer (and buzzer led) behavior (actual logic starts here)
  buttonState = digitalRead(BUTTON);
  if (buttonState == HIGH) {
    doubleClicked = false;
    justPressed = true;
    lastDebounce = currentMillis - previousMillis;
    if (lastDebounce >= 100) everSince = currentMillis;
    
    // Hold State
    if (lastDebounce > 400) {
      tone(BUZZER, 900);
      digitalWrite(BUZZER_LED, HIGH);
      curIndex = 0;
    }
  } else {
    previousMillis = currentMillis;
    if (lastDebounce >= 100 && lastDebounce <= 400) {
      
      // Double-Clicked State
      if (doubleClicked) {
        if ((currentMillis - everSince) < 1000) {
          tone(BUZZER, 2300);
          digitalWrite(BUZZER_LED, HIGH);
        }
        else {
          noTone(BUZZER);
          digitalWrite(BUZZER_LED, LOW);
        }
      } else { // Clicked State
        if ((currentMillis - everSince) < 200) {
          tone(BUZZER, 2200);
          digitalWrite(BUZZER_LED, HIGH);
        } else {
          noTone(BUZZER);
          digitalWrite(BUZZER_LED, LOW);
        }
      }
      
      if (justPressed) {
        curIndex++;
        justPressed = false;
      }
      if (curIndex >= 2) {
        curIndex = 0;
        doubleClicked = true;
      }
    }

    else {
      noTone(BUZZER);
      digitalWrite(BUZZER_LED, LOW);
    }
  }
  if ((currentMillis - everSince) > 500) {
    curIndex = 0;
  }
}

void lightUp(int ledNum) {
  for (int i = 0; i < NUM_LEDS; i++) {
    i != ledNum ? digitalWrite(ledPins[i], LOW) : digitalWrite(ledPins[i], HIGH);
  }
}