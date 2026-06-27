#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button Pins
const int btnPins[] = {12, 13, 9, 8}; // Floor 0, 1, 2, 3
const int trigPin = 3;
const int echoPin = 4;

// Seven Segment Pins (A, B, C, D, E, F, G)
const int segPins[] = {A0, A1, A2, A3, 2, 10, 11};

int currentFloor = 0;
bool welcomeActive = false;

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i = 0; i < 4; i++) pinMode(btnPins[i], INPUT_PULLUP);
  for (int i = 0; i < 7; i++) pinMode(segPins[i], OUTPUT);

  updateDisplay(0); 
  lcd.print("4-Floor Lift OK");
  delay(2000);
  lcd.clear();
}

void loop() {
  long distance = getDistance();

  // Proximity Greeting
  if (distance > 0 && distance < 40 && !welcomeActive) {
    lcd.clear();
    lcd.print("    Welcome!    ");
    welcomeActive = true;
  } else if (distance > 60) {
    welcomeActive = false; 
  }

  // Check all 4 buttons
  for (int i = 0; i < 4; i++) {
    if (digitalRead(btnPins[i]) == LOW && currentFloor != i) {
      simulateTravel(i);
    }
  }
}

void simulateTravel(int target) {
  lcd.clear();
  lcd.print("Going to Floor ");
  lcd.print(target);
  
  delay(3000); // Simulated travel time
  
  currentFloor = target;
  updateDisplay(target);

  lcd.clear();
  lcd.print("U have arrived");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("   Thank You    ");
  delay(2000);
  lcd.clear();
}

void updateDisplay(int floorNum) {
  // Common Anode Logic (0 = ON, 1 = OFF)
  // Patterns: {A, B, C, D, E, F, G}
  if (floorNum == 0) {
    int p[] = {0, 0, 0, 0, 0, 0, 1}; // 0
    for(int i=0; i<7; i++) digitalWrite(segPins[i], p[i]);
  } 
  else if (floorNum == 1) {
    int p[] = {1, 0, 0, 1, 1, 1, 1}; // 1
    for(int i=0; i<7; i++) digitalWrite(segPins[i], p[i]);
  } 
  else if (floorNum == 2) {
    int p[] = {0, 0, 1, 0, 0, 1, 0}; // 2
    for(int i=0; i<7; i++) digitalWrite(segPins[i], p[i]);
  } 
  else if (floorNum == 3) {
    int p[] = {0, 0, 0, 0, 1, 1, 0}; // 3
    for(int i=0; i<7; i++) digitalWrite(segPins[i], p[i]);
  }
}

long getDistance() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}