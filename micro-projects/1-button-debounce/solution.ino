#define LED_PIN0 4
#define LED_PIN1 7
#define LED_PIN2 8

#define BUTTON_PIN 2

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long lastDebounce = 0;
unsigned long everSince = 0;
int curIndex = 0;
bool justPressed = false;
bool doubleClicked = false;
int buttonState = LOW;
bool firstEncounter = true;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN0, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}

void lightUp(int ledNum);

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  currentMillis = millis();
  if (buttonState == HIGH) {
    doubleClicked = false;
    justPressed = true;
    lastDebounce = currentMillis - previousMillis;
    everSince = currentMillis;
  } else {
    previousMillis = currentMillis;
    if (lastDebounce >= 100 && lastDebounce <= 400) {
      if (doubleClicked) {
        lightUp(LED_PIN2);
      } else {
        lightUp(LED_PIN0);
      }
      if (justPressed) {
        curIndex++;
        justPressed = false;
      }
      if (curIndex >= 2) {
        curIndex = 0;
        doubleClicked = true;
        firstEncounter = false;
      }
    } else if (lastDebounce > 400) {
      lightUp(LED_PIN1);
    }
  }
  if ((currentMillis - everSince) > 500) {
    curIndex = 0;
  }
}

void lightUp(int ledNum) {
  digitalWrite(LED_PIN0, LOW);
  digitalWrite(LED_PIN1, LOW);
  digitalWrite(LED_PIN2, LOW);
  digitalWrite(ledNum, HIGH);
}
