// PINS
#define POTENTIOMETER A0
constexpr int LED1 = 2;
constexpr int LED2 = 4;
constexpr int LED3 = 7;
constexpr int LED4 = 8;
constexpr int LED5 = 12;
constexpr int NUM_LEDS = 5;
const int ledPins[NUM_LEDS] = { LED1, LED2, LED3, LED4, LED5 };

// VALUES THRESHOLD + HYSTERESIS
constexpr int THRESHOLD_ON = 500;
constexpr int THRESHOLD_OFF = 490;
bool switched = false;

// VALUES LED PATTERN
bool on = false;
unsigned long ledMillis = 0;
unsigned long ledDelay = 200;
int litLed1 = 0;
int litLed2 = 2;

void start() {
    pinMode(POTENTIOMETER, INPUT);
    for (int i = 0; i < NUM_LEDS; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
}

void lightsOff();
void updateLedPattern();
void loop() {
    int value = analogRead(POTENTIOMETER);
    
    // hysteresis logic
    if (!switched && value > THRESHOLD_ON) {
        on = true;
        switched = true;
    }
    if (switched && value < THRESHOLD_OFF) {
        on = false;
        switched = false;
    }
    
    if (on) {
        unsigned long currentMillis = millis();
        if (currentMillis - ledMillis > ledDelay) {
            ledMillis = currentMillis;
            updateLedPattern();
        }
    }
    else {
        lightsOff();
    }
}

void updateLedValues();
void updateLedPattern() {
    lightsOff();
    updateLedValues();
    digitalWrite(ledPins[litLed1], HIGH);
    digitalWrite(ledPins[litLed2], HIGH);
}

void updateLedValues() {
    litLed1++;
    litLed2++;
    if (litLed1 >= NUM_LEDS) {
        litLed1 = 0;
    }
    if (litLed2 >= NUM_LEDS) {
        litLed2 = 0;
    }
}

void lightsOff() {
    for (int i = 0; i < NUM_LEDS; i++) {
        digitalWrite(ledPins[i], LOW);
    }
}