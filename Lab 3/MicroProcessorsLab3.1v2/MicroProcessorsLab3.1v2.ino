#define LED_GREEN 4
#define LED_RED 5
#define BUTTON_1 3

#define COUNTER_TIME 500

unsigned long gCounter = 0;
volatile unsigned char gISRFlag1 = 0;
volatile unsigned char gISRFlag2 = 0;

void setup() {
  Serial.begin(9600);

  // Initialize I/Os
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(BUTTON_1, INPUT_PULLUP);

  // Configure Timers
noInterrupts(); // Disable interrupts during setup
  
  TCCR1A = 0;               // Normal operation
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC Mode, Prescaler 1024
  OCR1A = 15624;            // 1Hz = (16MHz / (1024 * (1 + OCR1A))) - 1
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer1 Compare Match Interrupt
  TCCR2A = (1 << WGM21);     // CTC Mode
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); // Prescaler 1024
  OCR2A = 156;               // 10Hz = (16MHz / (1024 * (1 + OCR2A))) - 1
  TIMSK2 |= (1 << OCIE2A);   // Enable Timer2 Compare Match Interrupt
  interrupts(); // Enable interrupts
}


void loop() {
  // Task 1 - Every 1 second
  if(gISRFlag1){
    // Reset Flag
    gISRFlag1 = 0;
    gCounter++;

    // Toggle Green LED
    digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
    Serial.print(F("Counter: "));
    Serial.println(gCounter);
  }

  // Task 2 - Every 100 ms
  if(gISRFlag2){
    // Reset Flag
    gISRFlag2 = 0;

    // Read Button
    if(digitalRead(BUTTON_1) == LOW){
      digitalWrite(LED_RED, HIGH);
    } else{
      digitalWrite(LED_RED, LOW);
    }
    
  }
  // Foreground Task - Every 3 seconds
  if (gCounter >= 3) {
    Serial.println(F("Hello from the microcontroller!"));
    gCounter = 0; // Reset counter
  }
}

ISR(TIMER1_COMPA_vect){
  // Set Flag
  gISRFlag1 = 1;
}

ISR(TIMER2_COMPA_vect){
  // Set Flag
  gISRFlag2 = 1;
}