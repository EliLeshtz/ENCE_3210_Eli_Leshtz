const int button1 = 2; // Button 1 (interrupt pin)

int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Input array
int y[10];                                   // Output array

volatile bool calculate = false; // Flag to trigger calculation

void setup() {
  pinMode(button1, INPUT_PULLUP);

  // Attach interrupt for Button 1
  attachInterrupt(digitalPinToInterrupt(button1), calculateFilterISR, FALLING);

  Serial.begin(9600);
}

void loop() {
  if (calculate) {
    calculate = false; // Clear the flag
    Serial.println("Calculating filtered array...");

    // Perform the filtering operation
    y[0] = 2 * x[0]; // Handle the first element (x[-1] is assumed to be 0)
    for (int n = 1; n < 10; n++) {
      y[n] = 2 * x[n] - x[n - 1];
    }

    // Print the filtered array
    Serial.println("Filtered array:");
    for (int n = 0; n < 10; n++) {
      Serial.print("y[");
      Serial.print(n);
      Serial.print("] = ");
      Serial.println(y[n]);
    }
  }
}

void calculateFilterISR() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 200) { // Debounce
    calculate = true; // Set flag to trigger calculation
  }
  lastInterruptTime = interruptTime;
}
