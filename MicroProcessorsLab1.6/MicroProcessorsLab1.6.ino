const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;
const int button1 = 7; // Button for operation selection
const int button2 = 8; // Button to execute operation

int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // First array
int arr2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; // Second array
int result[10]; // Third array for storing results

int operation = 0; // 0 = Add, 1 = Subtract, 2 = Multiply
bool operationSelected = false;

void setup() {
  // Initialize pins
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  // Ensure all LEDs are OFF at the start
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  // Start the serial monitor for debugging
  Serial.begin(9600);
  Serial.println("Press button1 to select an operation, and button2 to execute it.");
}

void loop() {
  // Handle operation selection (Button 1)
  if (digitalRead(button1) == LOW) {
    delay(200); // Debounce delay
    operation = (operation + 1) % 3; // Cycle through operations (0, 1, 2)
    operationSelected = true;

    // Turn on corresponding LED for the selected operation
    if (operation == 0) { // Addition
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
      digitalWrite(blueLED, LOW);
      Serial.println("Addition selected.");
    } else if (operation == 1) { // Subtraction
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      digitalWrite(blueLED, LOW);
      Serial.println("Subtraction selected.");
    } else if (operation == 2) { // Multiplication
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, LOW);
      digitalWrite(blueLED, HIGH);
      Serial.println("Multiplication selected.");
    }
  }

  // Handle operation execution (Button 2)
  if (digitalRead(button2) == LOW && operationSelected) {
    delay(200); // Debounce delay
    Serial.println("Performing operation...");

    // Perform the selected operation on the arrays
    for (int i = 0; i < 10; i++) {
      if (operation == 0) { // Addition
        result[i] = arr1[i] + arr2[i];
      } else if (operation == 1) { // Subtraction
        result[i] = arr1[i] - arr2[i];
      } else if (operation == 2) { // Multiplication
        result[i] = arr1[i] * arr2[i];
      }
    }

    // Turn off all LEDs after operation
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);

    // Display the results in the serial monitor
    Serial.println("Results:");
    for (int i = 0; i < 10; i++) {
      Serial.print("Result[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.println(result[i]);
    }

    // Turn on all LEDs briefly to indicate completion
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, HIGH);
    delay(1000); // Keep LEDs ON for 1 second
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);

    // Reset operationSelected to allow new selection
    operationSelected = false;
  }
}
