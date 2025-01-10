// Task1.ino
#include <Arduino.h>

int calculateTwiceSquare(int num) {
  return 2 * (num * num);
}

void setup() {
  Serial.begin(9600);
  int results[512];
  
  for (int i = 0; i <= 511; i++) {
    results[i] = calculateTwiceSquare(i);
    Serial.print("Number: ");
    Serial.print(i);
    Serial.print(" -> Twice the square: ");
    Serial.println(results[i]);
  }
}

void loop() {
  // Nothing to do here
}

