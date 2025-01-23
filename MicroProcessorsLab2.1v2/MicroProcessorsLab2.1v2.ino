volatile int button1Count = 0;
volatile int button2Count = 0;

void setup() {
  pinMode(2, INPUT_PULLUP); // Button 1
  pinMode(3, INPUT_PULLUP); // Button 2
  pinMode(4, OUTPUT);       // Red LED
  pinMode(5, OUTPUT);       // Green LED

  attachInterrupt(digitalPinToInterrupt(2), button1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), button2ISR, FALLING);
}

void loop() {
  // Copy the volatile variables to local variables to prevent conflicts
  int b1Count, b2Count;
  noInterrupts(); // Temporarily disable interrupts
  b1Count = button1Count;
  b2Count = button2Count;
  interrupts(); // Re-enable interrupts

  int difference = b1Count - b2Count;

  // Control the LEDs based on the count difference
  if (difference > 0) {
    digitalWrite(4, HIGH);  // Red ON
    digitalWrite(5, LOW);   // Green OFF
  } else if (difference == 0) {
    digitalWrite(4, HIGH);  // Both Red and Green ON
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(4, LOW);   // Red OFF
    digitalWrite(5, HIGH);  // Green ON
  }
}

void button1ISR() {
  static unsigned long lastInterruptTime1 = 0;
  unsigned long interruptTime1 = millis();

  // Debounce logic for Button 1
  if (interruptTime1 - lastInterruptTime1 > 50) { // 50ms debounce
    button1Count++;
  }
  lastInterruptTime1 = interruptTime1;
}

void button2ISR() {
  static unsigned long lastInterruptTime2 = 0;
  unsigned long interruptTime2 = millis();

  // Debounce logic for Button 2
  if (interruptTime2 - lastInterruptTime2 > 50) { // 50ms debounce
    button2Count++;
  }
  lastInterruptTime2 = interruptTime2;
}
