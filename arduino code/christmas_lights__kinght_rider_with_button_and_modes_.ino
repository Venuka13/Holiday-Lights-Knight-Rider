const int potPin = A0;                    // Speed control dial at the bottom
const int buttonPin = 3;                  // Your button connected to Pin 3
int ledPins[] = {13, 12, 11, 10, 9, 8, 7, 6}; // Your 8 LEDs in row order
int numLeds = 8;

int currentMode = 0;                      
const int totalModes = 5;                 // Total number of festive styles
int lastButtonState = HIGH;               // PULLUP default state (unpressed)

void setup() {
  // Initialize all 8 LED pins as digital outputs
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Initialize the button pin with the internal anti-static shield
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Constantly check if the button is being pressed to change modes
  checkButton();

  // Run the current light pattern based on the active mode
  switch (currentMode) {
    case 0: knightRiderMode(); break;   // Mode 1: Classic Knight Rider bounce
    case 1: marqueeWaveMode(); break;   // Mode 2: Alternating Christmas blink (Even/Odd)
    case 2: sparkleMode(); break;       // Mode 3: Random twinkling stars
    case 3: collisionMode(); break;     // Mode 4: Inward crashing wave
    case 4: centerFanMode(); break;     // Mode 5: Center-out fan ending on ONLY LED 4
  }
}

// Cleans up static noise and registers light button taps perfectly
void checkButton() {
  int buttonState = digitalRead(buttonPin);
  
  // Detects the exact instant the button drops to Ground (LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(200); // Strong debounce filter to block ghost clicks and double-tapping
    allOff();   // Reset lights instantly before changing modes
    currentMode = (currentMode + 1) % totalModes; // Move to next mode (0 to 4)
  }
  lastButtonState = buttonState;
}

// Turn off all lights instantly when shifting modes
void allOff() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Fetches knob speed dynamically from the potentiometer
int getSpeed() {
  int potValue = analogRead(potPin);
  // Maps the dial (0-1023) to a delay time between 20ms (fast) and 350ms (slow)
  return map(potValue, 0, 1023, 20, 350);
}

// ==========================================
// FESTIVE CHRISTMAS LIGHT MODES
// ==========================================

// Mode 0: The Classic Bounce
void knightRiderMode() {
  for (int i = 0; i < numLeds; i++) {
    checkButton(); if(currentMode != 0) return; // Exit immediately if button is clicked
    digitalWrite(ledPins[i], HIGH);
    delay(getSpeed());
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = numLeds - 2; i > 0; i--) {
    checkButton(); if(currentMode != 0) return;
    digitalWrite(ledPins[i], HIGH);
    delay(getSpeed());
    digitalWrite(ledPins[i], LOW);
  }
}

// Mode 1: Alternating Marquee Wave
void marqueeWaveMode() {
  // Flash even lights ON, odd lights OFF
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], (i % 2 == 0) ? HIGH : LOW);
  }
  delay(getSpeed() * 2);
  checkButton(); if(currentMode != 1) return;

  // Flash even lights OFF, odd lights ON
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], (i % 2 == 0) ? LOW : HIGH);
  }
  delay(getSpeed() * 2);
}

// Mode 2: Random Sparkle
void sparkleMode() {
  allOff();
  int randomLed = random(0, numLeds); // Pick a random light
  digitalWrite(ledPins[randomLed], HIGH);
  delay(getSpeed() / 2);
  digitalWrite(ledPins[randomLed], LOW);
  delay(getSpeed() / 2);
}

// Mode 3: Inward Collision Wave
void collisionMode() {
  for (int i = 0; i < numLeds / 2; i++) {
    checkButton(); if(currentMode != 3) return;
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[numLeds - 1 - i], HIGH); // Light up mirror image from bottom
    delay(getSpeed() * 1.5);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[numLeds - 1 - i], LOW);
  }
}

// Mode 4: Center-Out Fan (Ends strictly on LED 4 / Pin 10)
void centerFanMode() {
  // 1. Fan Outward: Start from the middle-left (LED 4) and zoom out to the edges
  for (int i = 3; i >= 0; i--) {
    checkButton(); if(currentMode != 4) return;
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[numLeds - 1 - i], HIGH);
    delay(getSpeed() * 1.5);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[numLeds - 1 - i], LOW);
  }

  // 2. Snap Inward: Zoom from the edges back toward the center
  for (int i = 0; i < 3; i++) {
    checkButton(); if(currentMode != 4) return;
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[numLeds - 1 - i], HIGH);
    delay(getSpeed() * 1.5);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[numLeds - 1 - i], LOW);
  }

  // 3. Single Center Hit: Flash ONLY LED 4 (which is at index 3 in our pin array)
  checkButton(); if(currentMode != 4) return;
  digitalWrite(ledPins[3], HIGH); 
  delay(getSpeed() * 1.5);
  digitalWrite(ledPins[3], LOW);  
}
