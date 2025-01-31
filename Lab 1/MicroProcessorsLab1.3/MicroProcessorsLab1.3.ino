const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;

char letters[] = "RGGBBBGRRBGG"; // Example array of letters
int countR = 0, countG = 0, countB = 0;

void setup() {
  // Initialize pins as outputs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  // Ensure all LEDs start in the OFF state
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  // Start the serial monitor for debugging
  Serial.begin(9600);
  
  // Iterate through the array to count and control LEDs
  for (int i = 0; i < sizeof(letters) - 1; i++) {
    if (letters[i] == 'R') {
      countR++;
      digitalWrite(redLED, HIGH);
      delay(200); // Turn on the LED briefly
      digitalWrite(redLED, LOW);
    } else if (letters[i] == 'G') {
      countG++;
      digitalWrite(greenLED, HIGH);
      delay(200);
      digitalWrite(greenLED, LOW);
    } else if (letters[i] == 'B') {
      countB++;
      digitalWrite(blueLED, HIGH);
      delay(200);
      digitalWrite(blueLED, LOW);
    }
    delay(200);
  }
  
  // Display the counts in the serial monitor
  Serial.println("Counts:");
  Serial.print("R: ");
  Serial.println(countR);
  Serial.print("G: ");
  Serial.println(countG);
  Serial.print("B: ");
  Serial.println(countB);
}

void loop() {
  // Nothing to do in loop
}
