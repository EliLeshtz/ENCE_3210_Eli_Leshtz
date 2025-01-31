const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;
const int buttonPin = 7;

bool isRunning = false;  // To track if the sequence is running
bool lastButtonState = HIGH; // Previous state of the button (HIGH = not pressed)

void setup() {
  // Initialize pins as outputs and input
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Button with internal pull-up

  // Ensure all LEDs are OFF at the start
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  // Start the serial monitor for debugging
  Serial.begin(9600);
  Serial.println("Press the button to start or stop the LED sequence.");
}

void loop() {
  // Read the current button state
  bool currentButtonState = digitalRead(buttonPin);

  // Detect a button press (transition from HIGH to LOW)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    delay(50); // Debounce delay
    isRunning = !isRunning; // Toggle the running state
    Serial.println(isRunning ? "LED sequence started." : "LED sequence stopped.");
  }

  // Update the last button state
  lastButtonState = currentButtonState;

  // Run the LED sequence if isRunning is true
  if (isRunning) {
    runLEDSequence();

    // Check button state during the sequence to allow stopping mid-sequence
    if (digitalRead(buttonPin) == LOW) {
      delay(50); // Debounce delay
      isRunning = false; // Stop the sequence
      Serial.println("LED sequence stopped.");
    }
  }
}

void runLEDSequence() {
  // R
  digitalWrite(redLED, HIGH);
  delay(500);
  digitalWrite(redLED, LOW);
  delay(500);

  // RG
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, HIGH);
  delay(500);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  delay(500);

  // RGB
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  delay(500);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(500);

  // GB
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  delay(500);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(500);

  // B
  digitalWrite(blueLED, HIGH);
  delay(500);
  digitalWrite(blueLED, LOW);
  delay(500);

  // RB
  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, HIGH);
  delay(500);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(500);
}
