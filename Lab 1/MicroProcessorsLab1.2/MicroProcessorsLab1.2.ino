// Task3.ino
#include <Arduino.h>

#define ARRAY_SIZE 50
int dataArray[ARRAY_SIZE] = { 45, 23, 67, 89, 12, 34, 65, 98, 13, 55, 44, 76, 87, 21, 10, 
                              99, 43, 77, 56, 54, 88, 92, 18, 61, 31, 47, 39, 70, 26, 53, 
                              80, 81, 36, 14, 90, 74, 66, 28, 48, 17, 57, 62, 78, 41, 27, 
                              29, 30, 38, 50, 63 }; // Example data
int secondMax;

void findSecondMax() {
  int max = -32768; // Smallest integer value for Arduino
  secondMax = -32768;

  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (dataArray[i] > max) {
      secondMax = max;
      max = dataArray[i];
    } else if (dataArray[i] > secondMax && dataArray[i] != max) {
      secondMax = dataArray[i];
    }
  }
}

void setup() {
  Serial.begin(9600);
  findSecondMax();

  Serial.println("Array:");
  for (int i = 0; i < ARRAY_SIZE; i++) {
    Serial.print(dataArray[i]);
    Serial.print(i < ARRAY_SIZE - 1 ? ", " : "\n");
  }

  Serial.print("Second Maximum Value: ");
  Serial.println(secondMax);
}

void loop() {
  // Nothing to do here
}
