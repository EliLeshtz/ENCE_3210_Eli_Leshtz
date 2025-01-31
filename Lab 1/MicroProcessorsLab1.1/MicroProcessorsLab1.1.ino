// Task2.ino
#include <Arduino.h>
#include <math.h>

void setup() {
  Serial.begin(9600);
  float results[361];

  for (int i = 0; i <= 360; i++) {
    results[i] = cos(radians(i));
    Serial.print("Degree: ");
    Serial.print(i);
    Serial.print(" -> Cosine: ");
    Serial.println(results[i], 6); // Print cosine with 6 decimal places
  }
}

void loop() {
  // Nothing to do here
}