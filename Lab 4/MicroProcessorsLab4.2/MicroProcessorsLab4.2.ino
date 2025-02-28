#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int potPin = A0;  // Potentiometer simulating battery voltage
const int buttonPin = 6; // Button simulating solar panel voltage state
bool solarActive = false; // Tracks if solar panel voltage is above 2.5V
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

bool chargingBattery = false;  // Tracks if battery is charging

void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT);  // Use internal pull-up resistor

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    display.clearDisplay();
    display.display();
}

void loop() {
    // Read battery voltage
    int batteryVoltage = analogRead(potPin);
    float batteryLevel = (batteryVoltage / 1023.0) * 5.0; // Convert to 0-5V range

    // Debounce button press (simulating solar panel voltage status)
    bool buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && lastButtonState == HIGH && (millis() - lastDebounceTime) > debounceDelay) {
        solarActive = !solarActive;  // Toggle solar panel voltage status
        lastDebounceTime = millis();

        // Print solar panel status to Serial Monitor
        if (solarActive) {
            Serial.println("Solar Panel Voltage: 2.5V or higher (Solar Active)");
        } else {
            Serial.println("Solar Panel Voltage: Below 2.5V (Battery Active)");
        }
    }
    lastButtonState = buttonState;

    // Determine power source
    String powerStatus;
    
    if (chargingBattery) {
        powerStatus = "Charging Battery";
    } else if (solarActive) {
        powerStatus = "Solar Powers Processor";
    } else {
        powerStatus = "Battery Powers Processor";
    }

    // If battery voltage < solar panel voltage, start charging
    if (solarActive && batteryLevel < 2.5) {
        chargingBattery = true;
    }

    // If battery reaches full charge (e.g., 4.2V), stop charging
    if (chargingBattery && batteryLevel >= 4.8) {
        chargingBattery = false;
    }

    // Update OLED Display
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(10, 0);
    display.print("Battery: ");
    display.print(batteryLevel, 2);
    display.print("V");

    display.setCursor(10, 10);
    display.print(powerStatus);

    display.display();
    delay(200);
}
