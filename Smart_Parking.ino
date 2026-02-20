#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <Servo.h> 

// --- Configuration & Pin Definitions ---
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myservo;

const int IR_ENTRY = 2;   // IR Sensor at Entry
const int IR_EXIT  = 3;   // IR Sensor at Exit
const int SERVO_PIN = 4;  // Servo Motor Pin

// --- System Variables ---
int totalSlots = 4;       // Maximum parking capacity
int availableSlots = 4;   
int flagEntry = 0;
int flagExit = 0;

void setup() {
  Serial.begin(9600); 
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Setup Pins
  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_EXIT, INPUT);
  
  // Setup Servo
  myservo.attach(SERVO_PIN);
  myservo.write(100); // Initial Gate Position (Closed)

  // Welcome Screen
  lcd.setCursor(0, 0);
  lcd.print("   ARDUINO    ");
  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay(2000);
  lcd.clear();  
}

void loop() { 
  // --- ENTRY LOGIC ---
  if(digitalRead(IR_ENTRY) == LOW && flagEntry == 0) {
    if(availableSlots > 0) {
      flagEntry = 1;
      if(flagExit == 0) {
        myservo.write(0); // Open Gate
        availableSlots--;
      }
    } else {
      showFullMessage();
    }
  }

  // --- EXIT LOGIC ---
  if(digitalRead(IR_EXIT) == LOW && flagExit == 0) {
    flagExit = 1;
    if(flagEntry == 0) {
      myservo.write(0); // Open Gate
      availableSlots++;
    }
  }

  // --- CLOSE GATE LOGIC ---
  if(flagEntry == 1 && flagExit == 1) {
    delay(1000);
    myservo.write(100); // Close Gate
    flagEntry = 0;
    flagExit = 0;
  }

  // --- UPDATE DISPLAY ---
  updateDisplay();
}

// Function to update the main screen
void updateDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(availableSlots);
  lcd.print("   "); // Clear extra digits
}

// Function to show 'Full' status
void showFullMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    SORRY :(    ");  
  lcd.setCursor(0, 1);
  lcd.print("  Parking Full  "); 
  delay(2000);
  lcd.clear();
}