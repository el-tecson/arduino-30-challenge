// ========================================
// # 4. Priority override system

// * Normal LED pattern
// * Emergency input (ball switch) overrides everything
// ========================================

// Get Pin numbers
#define LED0 2
#define LED1 4
#define LED2 7
#define LED3 8
#define SIG 12

// For debounce
#define DEBOUNCE_MS 100

// LEDs
const int NUM_LEDS = 4;
const int ledPins[NUM_LEDS] = { LED0, LED1, LED2, LED3 };
unsigned long previousMillis[NUM_LEDS] = { 0, 0, 0, 0 };
const long inactiveIntervals[NUM_LEDS] = { 1000, 2000, 3000, 4000 }; // normal pattern
const long activeIntervals[NUM_LEDS] = { 100, 200, 300, 400 };       // 10x faster pattern
int ledStates[NUM_LEDS] = { LOW, LOW, LOW, LOW };

bool stableState = false;
unsigned long lastChange = 0;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(SIG, INPUT_PULLUP);  // use internal pull-up for digital switch
}

void loop() {
  unsigned long currentMillis = millis();
  bool raw = !digitalRead(SIG);

  // Debounce logic
  if (raw != stableState && (currentMillis - lastChange > DEBOUNCE_MS)) {
    stableState = raw;
    lastChange = currentMillis;
  }

  // Change pattern speed if ball switch is tilted
  for (int i = 0; i < NUM_LEDS; i++) {
    long interval = stableState ? activeIntervals[i] : inactiveIntervals[i];

    if (currentMillis - previousMillis[i] >= interval) {
      previousMillis[i] = currentMillis;
      ledStates[i] = !ledStates[i];
      digitalWrite(ledPins[i], ledStates[i]);
    }
  }
}
