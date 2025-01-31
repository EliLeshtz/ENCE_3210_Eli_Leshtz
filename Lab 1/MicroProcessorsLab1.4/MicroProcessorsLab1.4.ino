const int redLED = 9;
const int greenLED = 10;

char array[] = "ABCDEGHIJKLMNOPQRSTUVXYZ"; // Example array
char pattern[] = "GHI";                    // Pattern to detect
int patternCount = 0;                      // Counter for pattern occurrences

void setup() {
  // Initialize pins as outputs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Ensure LEDs are OFF at the start
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);

  // Start the serial monitor for debugging
  Serial.begin(9600);

  // Search for the pattern in the array
  for (int i = 0; i < sizeof(array) - sizeof(pattern); i++) {
    if (strncmp(&array[i], pattern, sizeof(pattern) - 1) == 0) {
      patternCount++;
    }
  }

  // Control the LEDs based on the pattern count
  if (patternCount > 0) {
    digitalWrite(greenLED, HIGH); // Green LED for pattern found
  } else {
    digitalWrite(redLED, HIGH);  // Red LED for pattern not found
  }

  // Print the pattern count to the serial monitor
  Serial.println("Pattern Detection Result:");
  Serial.print("Pattern found ");
  Serial.print(patternCount);
  Serial.println(" times.");
}

void loop() {
  // Nothing to do in loop
}
