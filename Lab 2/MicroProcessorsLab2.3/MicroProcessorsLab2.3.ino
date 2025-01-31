const int button1 = 2; // Button 1 (interrupt pin) - Select operation
const int button2 = 3; // Button 2 (interrupt pin) - Perform operation

const int redLED = 9;     // Red LED for Addition
const int greenLED = 10;  // Green LED for Subtraction
const int blueLED = 11;   // Blue LED for Multiplication

int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // First array
int arr2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; // Second array
int result[10];                               // Array to store results

volatile int operation = 0;  // Selected operation: 0 = Add, 1 = Subtract, 2 = Multiply
volatile bool execute = false; // Flag to indicate execution of the operation

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  // Turn off all LEDs initially
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(button1), selectOperationISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2), performOperationISR, FALLING);

  Serial.begin(9600);
}

void loop() {
  if (execute) {
    execute = false; // Clear the flag
    Serial.println("Performing operation...");
    for (int i = 0; i < 10; i++) {
      if (operation == 0) { // Addition
        result[i] = arr1[i] + arr2[i];
      } else if (operation == 1) { // Subtraction
        result[i] = arr1[i] - arr2[i];
      } else if (operation == 2) { // Multiplication
        result[i] = arr1[i] * arr2[i];
      }
    }

    // Print results
    Serial.println("Results:");
    for (int i = 0; i < 10; i++) {
      Serial.print("Result[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.println(result[i]);
    }

    // Indicate completion with all LEDs ON briefly
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, HIGH);
    delay(1000);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  }
}

void selectOperationISR() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 200) { // Debounce
    operation = (operation + 1) % 3; // Cycle through operations (0, 1, 2)
    // Indicate selected operation with LEDs
    digitalWrite(redLED, operation == 0);
    digitalWrite(greenLED, operation == 1);
    digitalWrite(blueLED, operation == 2);

    const char* opName = (operation == 0) ? "Addition" : (operation == 1) ? "Subtraction" : "Multiplication";
    Serial.print(opName);
    Serial.println(" selected.");
  }
  lastInterruptTime = interruptTime;
}

void performOperationISR() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 200) { // Debounce
    execute = true; // Set flag to perform the operation
  }
  lastInterruptTime = interruptTime;
}
