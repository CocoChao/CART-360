#define PIN_LED_BUTTON_1  3   
#define PIN_LED_BUTTON_2  5   
#define PIN_LED_BUTTON_3  9 
#define PIN_LED_BUTTON_4  10  
#define PIN_PIEZO         11  

#define LED_BUTTON_COUNT  4   // Number of LEDs & buttons

static int buttonLookup[LED_BUTTON_COUNT] = { PIN_LED_BUTTON_1, PIN_LED_BUTTON_2, PIN_LED_BUTTON_3, PIN_LED_BUTTON_4 };
static long gameSeed;

// Returns the period in microseconds of the half-cycle tone for each button.
// Light sequence does not change no matter the press-button input (Red, Yellow, Green, Blue)
// Sequence lights up when input is false
int ledButtonHalfPeriod(int button) {
  switch (button) {
    case PIN_LED_BUTTON_1:
      return 1911;
    case PIN_LED_BUTTON_2:
      return 1703;
    case PIN_LED_BUTTON_3:
      return 1517;
    case PIN_LED_BUTTON_4:
      return 1432;
  }
  return 3822;
}

// Button needs to be pressed at correct timing, which is half a period (not too fast, nor too slow). 
// If wrong button is pressed, light sequence will play (4,3,2,1)
bool checkButtonPush(int button) {
  bool result = false;
  pinMode(button, INPUT);   
  digitalWrite(button, HIGH);

 // Time between the moment LED lights and the moment the button is pushed.
  int halfPeriod = ledButtonHalfPeriod(button);

 // LED light waits half a period to flash the next LED of the sequence when buttons are played correctly.
  while (digitalRead(button) == LOW) {
    // Button is being pushed
    result = true;
    digitalWrite(PIN_PIEZO, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(PIN_PIEZO, LOW);
    delayMicroseconds(halfPeriod);
  }
  return result; 
}
// When the previous sequence is played, it outputs the previous sequence plus an additional light to the sequence 
int getButtonPush(void) {
  for (int i = 0; i < LED_BUTTON_COUNT; ++i) {
    if (checkButtonPush(buttonLookup[i])) {
      return i;
    }
  }
// If else, return false and the cycle restarts after all the light turns on
  return -1;
}
// The buzzer plays a feedback sound 
void displayLightAndSound(int led, int duration) {
  if (led >= 0) {
    pinMode(led, OUTPUT);   // Set led cathode pin as output
    digitalWrite(led, LOW); 
  }
  
  int halfPeriod = ledButtonHalfPeriod(led);
  
  // 500 milliseconds  
  long cycleCount = (long)duration * 500;
  cycleCount /= halfPeriod;
  for (; cycleCount > 0; --cycleCount) {
    digitalWrite(PIN_PIEZO, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(PIN_PIEZO, LOW);
    delayMicroseconds(halfPeriod);
  }
  
  if (led >= 0) {
    pinMode(led, INPUT);      // Set led cathode pin as input
    digitalWrite(led, HIGH);  
  }
}

void startUpLightsAndSound(void) {
  // Power-up lights and sound
  displayLightAndSound(PIN_LED_BUTTON_1, 100);
  displayLightAndSound(PIN_LED_BUTTON_2, 100);
  displayLightAndSound(PIN_LED_BUTTON_3, 100);
  displayLightAndSound(PIN_LED_BUTTON_4, 100);

  // Wait for button push to continue
  while (getButtonPush() < 0) {
    delay(100);
  }
  
  // Delay a bit before starting
  delay(500);
}


// the setup routine runs:
void setup() {
  // Set button pins as input
  pinMode(PIN_LED_BUTTON_1, INPUT);
  pinMode(PIN_LED_BUTTON_2, INPUT);
  pinMode(PIN_LED_BUTTON_3, INPUT);
  pinMode(PIN_LED_BUTTON_4, INPUT);
  
  // Set the piezo pin as output
  pinMode(PIN_PIEZO, OUTPUT);

  // Power-up lights and sound
  startUpLightsAndSound();

  // Randomize the first game
  gameSeed = micros();
}

// the loop routine runs over and over again forever:
void loop() {
  static int sequenceLength = 1;
  int i;
  
  // Display current sequence
  // Play light and sound after buttons are pressed with a delay of 250 milliseconds in between
  randomSeed(gameSeed);
  for (i = sequenceLength; i > 0; --i) {
    displayLightAndSound(buttonLookup[random(LED_BUTTON_COUNT)], 250);
    delay(250);
  }
  // Precision and timing when the button is pushed.
  randomSeed(gameSeed);
  for (int matches = 0; matches < sequenceLength; ++matches) {
    int button = -1;
    int timeout;
    // Wait for the player to press a button (with 3 second timeout)
    for (button = -1, timeout = 30; timeout && button < 0; --timeout) {
      button = getButtonPush();
      delay(100);
    }
  
    // Check if the correct button was pushed
    if (button != random(LED_BUTTON_COUNT)) {
      // Play sad sound and start a new game
      displayLightAndSound(-1, 1000);
      gameSeed = micros();
      delay(1000);
      sequenceLength = 0;
      startUpLightsAndSound();
    }
  }
  // Always adds + 1 to the stored sequence length
  ++sequenceLength;
  delay(1000);
}



 
