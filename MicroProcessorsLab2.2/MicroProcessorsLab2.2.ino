const int redLED = 9;     // Red LED pin
const int greenLED = 10;  // Green LED pin
const int blueLED = 11;   // Blue LED pin
const int button1 = 2;    // Button 1 (interrupt pin)

volatile bool sequenceRunning = false; // To track if the sequence is active
volatile bool stopSequence = false;    // To signal when to stop the sequence

unsigned long previousMillis = 0;      // For non-blocking timing
const unsigned long interval = 500;   // Interval for each step in the sequence
int currentStep = 0;                   // Current step in the sequence

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(button1, INPUT_PULLUP);      // Button with pull-up resistor

  // Ensure all LEDs are OFF initially
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  // Attach interrupt to button1
  attachInterrupt(digitalPinToInterrupt(button1), toggleSequenceISR, FALLING);

  Serial.begin(9600);
}

void loop() {
  // If sequenceRunning is true, execute the LED sequence
  if (sequenceRunning) {
    unsigned long currentMillis = millis();

    // Execute the sequence step if the interval has passed
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Run the current step of the LED sequence
      runLEDSequenceStep(currentStep);

      // Advance to the next step
      currentStep = (currentStep + 1) % 6; // Cycle through 6 steps
    }

    // If stopSequence is true, stop immediately
    if (stopSequence) {
      stopSequence = false;        // Clear the stop flag
      sequenceRunning = false;     // Stop the sequence
      turnOffAllLEDs();            // Turn off all LEDs
      Serial.println("Sequence stopped by interrupt.");
    }
  }
}

void toggleSequenceISR() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 200) { // Debounce check
    if (sequenceRunning) {
      stopSequence = true; // Set stop flag if sequence is running
    } else {
      sequenceRunning = true; // Start sequence if not running
      currentStep = 0;        // Reset to the first step
      previousMillis = millis(); // Reset the timer
      Serial.println("Sequence started.");
    }
  }
  lastInterruptTime = interruptTime;
}

void runLEDSequenceStep(int step) {
  // Turn off all LEDs before the next step
  turnOffAllLEDs();

  // Execute the current step
  switch (step) {
    case 0: // Red
      digitalWrite(redLED, HIGH);
      break;
    case 1: // Red + Green
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, HIGH);
      break;
    case 2: // Red + Green + Blue
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, HIGH);
      digitalWrite(blueLED, HIGH);
      break;
    case 3: // Green + Blue
      digitalWrite(greenLED, HIGH);
      digitalWrite(blueLED, HIGH);
      break;
    case 4: // Blue
      digitalWrite(blueLED, HIGH);
      break;
    case 5: // Red + Blue
      digitalWrite(redLED, HIGH);
      digitalWrite(blueLED, HIGH);
      break;
  }
}

void turnOffAllLEDs() {
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
}
