#define LED_PIN0 4
#define LED_PIN1 7
#define LED_PIN2 8
#define BUTTON_PIN 2

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long lastDebounce = 0;
unsigned long everSince = 0;

bool justPressed = false;
bool doubleClicked = false;

int buttonState = LOW;
int curIndex = 0;

const int NUM_STATES = 8;
const int NUM_LEDS = 3;
int ledPins[NUM_LEDS] = {LED_PIN0, LED_PIN1, LED_PIN2};
int state = 0;

int States[NUM_STATES][NUM_LEDS] = {
  {LOW, LOW, LOW},
  {HIGH, LOW, LOW},
  {LOW, HIGH, LOW},
  {LOW, LOW, HIGH},
  {HIGH, HIGH, LOW},
  {HIGH, LOW, HIGH},
  {LOW, HIGH, HIGH},
  {HIGH, HIGH, HIGH}
};

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  for (int i = 0; i < NUM_LEDS; i++) pinMode(ledPins[i], OUTPUT);
}

void incrementState();
void changeState(int index);

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  currentMillis = millis();

  if (buttonState == LOW) {
    doubleClicked = false;
    justPressed = true;
    lastDebounce = currentMillis - previousMillis;

    if (lastDebounce >= 100) everSince = currentMillis;
    if (lastDebounce > 400) {
      changeState(0);
      curIndex = 0;
    }

  } else {
    previousMillis = currentMillis;

    if (lastDebounce >= 100 && lastDebounce <= 400) {
      if (doubleClicked) changeState(NUM_STATES - 1);

      if (justPressed) {
        curIndex++;
        justPressed = false;
        incrementState();
      }

      if (curIndex >= 2) {
        curIndex = 0;
        doubleClicked = true;
      }
    }
  }

  if ((currentMillis - everSince) > 400) curIndex = 0;
}

void incrementState() {
  state++;
  if (state >= NUM_STATES) state = 0;
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(ledPins[i], States[state][i]);
}

void changeState(int index) {
  state = index;
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(ledPins[i], States[state][i]);
}
