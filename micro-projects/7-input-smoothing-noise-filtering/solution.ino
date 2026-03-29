#define POTENTIOMETER A0
constexpr int led1 = 3;
constexpr int led2 = 5;
constexpr int led3 = 6;
constexpr int led4 = 9;
constexpr int led5 = 10;
const int NUM_LEDS = 5;
const int ledPins[NUM_LEDS] = { led1, led2, led3, led4, led5 };

const int ON_THRESHOLD = 500;
const int OFF_THRESHOLD = 450;
bool on = false;

const int VALUE_THRESHOLD = 50;
int values[VALUE_THRESHOLD] = { 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void setup() {
  Serial.begin(9600);
  pinMode(POTENTIOMETER, INPUT);
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  int initial = analogRead(POTENTIOMETER);
  for (int i = 0; i < VALUE_THRESHOLD; i++) {
    values[i] = initial;
  }
}

int getAvg(int numArrLen, int numArr[]);
void appendValue(int value);
void lightUpLeds(bool value);
void loop() {
  int raw = analogRead(POTENTIOMETER);
  appendValue(raw);
  int stable = getAvg(VALUE_THRESHOLD, values);
  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print(" | Stable: ");
  Serial.println(stable);

  if (stable >= ON_THRESHOLD) {
    on = true;
  } else if (stable <= OFF_THRESHOLD) {
    on = false;
  }
  lightUpLeds(on);
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

void lightUpLeds(bool value) {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(ledPins[i], value);
  }
}
