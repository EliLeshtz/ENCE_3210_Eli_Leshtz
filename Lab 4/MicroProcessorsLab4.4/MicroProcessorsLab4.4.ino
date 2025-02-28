// Pin Definitions
const int sensorPin = A0;
const int fanPin = 9;
const int buttonOnOff = 2;
const int buttonSensitivity = 3;

// Variables
bool fanState = false;
int sensitivityLevel = 1; // 1: Low, 2: Medium, 3: High
const int numSamples = 100;
unsigned long lastDebounceTimeOnOff = 0;
unsigned long lastDebounceTimeSensitivity = 0;
const unsigned long debounceDelay = 50;
volatile bool powerPressed = false;
volatile bool sensitivityPressed = false;
int lastPWMValue = 0;
unsigned long lastTempReadTime = 0;
const unsigned long tempReadInterval = 5000;
float lastAvgTemp = 0.0;

void setup() {
    pinMode(fanPin, OUTPUT);
    pinMode(buttonOnOff, INPUT);
    pinMode(buttonSensitivity, INPUT);
    attachInterrupt(digitalPinToInterrupt(buttonOnOff), powerISR, RISING);
    attachInterrupt(digitalPinToInterrupt(buttonSensitivity), sensitivityISR, RISING);
    Serial.begin(9600);
}

void loop() {
    if (powerPressed) {
        fanState = !fanState;
        Serial.println(fanState ? "Fan turned ON" : "Fan turned OFF");
        updateFanSpeed(); // Ensure fan updates immediately on power change
        powerPressed = false;
    }
    
    if (sensitivityPressed) {
        sensitivityLevel++;
        if (sensitivityLevel > 3) sensitivityLevel = 1;
        Serial.print("Sensitivity changed to level: ");
        Serial.println(sensitivityLevel);
        updateFanSpeed(); // Only update LED when sensitivity changes
        sensitivityPressed = false;
    }
    
    if (millis() - lastTempReadTime >= tempReadInterval) {
        lastAvgTemp = readTemperature();
        Serial.print("Average Temperature: ");
        Serial.println(lastAvgTemp);
        updateFanSpeed();
        lastTempReadTime = millis();
    }
}

void updateFanSpeed() {
    if (fanState) {
        int pwmValue = mapTemperatureToPWM(lastAvgTemp, sensitivityLevel);
        if (pwmValue != lastPWMValue) {
            analogWrite(fanPin, pwmValue); // Adjust LED brightness (fan speed)
            lastPWMValue = pwmValue;
        }
    } else {
        analogWrite(fanPin, 0);  // Turn off LED when fan is off
        lastPWMValue = 0;
    }
}

float readTemperature() {
    long sum = 0;
    for (int i = 0; i < numSamples; i++) {
        sum += analogRead(sensorPin);
        delay(50); // Spread samples over 5 seconds
    }
    float avgReading = sum / (float)numSamples;
    float voltage = avgReading * (5.0 / 1023.0);
    return voltage * 100.0; // Convert to temperature correctly
}

int mapTemperatureToPWM(float temperature, int sensitivity) {
    int pwmValue = 0;
    switch (sensitivity) {
        case 1: // Low sensitivity: PWM changes slowly with temperature
            pwmValue = map(temperature, 0, 50, 50, 255); break; // Low Sensitivity
        case 2: // Medium sensitivity: PWM changes more directly with temperature
            pwmValue = map(temperature, 0, 50, 30, 255); break; // Medium Sensitivity
        case 3: // High sensitivity: PWM changes quickly with temperature
            pwmValue = map(temperature, 0, 50, 10, 255); break; // High Sensitivity
    }
    return constrain(pwmValue, 0, 255); // Ensure PWM is within valid range
}

void powerISR() {
    powerPressed = true;
}

void sensitivityISR() {
    sensitivityPressed = true;
}
