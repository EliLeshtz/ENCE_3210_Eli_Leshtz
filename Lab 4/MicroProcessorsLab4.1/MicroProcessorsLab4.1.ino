const int bitDepth = 14;  
const float vRef = 3.0;  

float testVoltages[] = {0.42, 0.83, 1.65, 2.752};  

// Simulated SAR ADC conversion
int SAR_ADC(float Vin) {
    int result = 0;
    int mask = 1 << (bitDepth - 1);  

    for (int i = 0; i < bitDepth; i++) {
        result |= mask;  
        float Vtest = (result / (float)(1 << bitDepth)) * vRef;

        if (Vtest > Vin) {  
            result &= ~mask;  
        }
        mask >>= 1;  
    }
    return result;
}

void setup() {
    Serial.begin(9600);
    Serial.println("14-bit SAR ADC Simulation");

    for (int i = 0; i < 4; i++) {
        int digitalValue = SAR_ADC(testVoltages[i]);
        float convertedVoltage = (digitalValue / (float)(1 << bitDepth)) * vRef;

        Serial.print("Input Voltage: ");
        Serial.print(testVoltages[i], 4);
        Serial.print("V -> Digital Code: ");
        Serial.print(digitalValue);
        Serial.print(" -> Converted Voltage: ");
        Serial.print(convertedVoltage, 4);
        Serial.println("V");
    }
}

void loop() {
}
