#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR_A_PIN 15  // Pin for sensor A
#define SENSOR_B_PIN 23  // Pin for sensor B
#define SERVO_PIN 19     // Pin for the servo
#define MAX_CARS 3       // Maximum number of cars in the parking lot

Servo myServo;  // Create object to control the servo

// LCD configuration (0x27 is common address)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 16x2 LCD

// Counters
int counterA = 0;  // Incoming cars counter (sensor A)
int counterB = 0;  // Outgoing cars counter (sensor B)
int totalCarsCounter = 0;  // Total cars in the parking lot

void setup() {
  pinMode(SENSOR_A_PIN, INPUT);  // Configure sensor A as input
  pinMode(SENSOR_B_PIN, INPUT);  // Configure sensor B as input
  Serial.begin(115200);          // Start serial communication for debugging
  
  myServo.attach(SERVO_PIN);     // Attach pin 19 to the servo
  myServo.write(90);             // Initial servo position (90°)
  
  // Start I2C communication (default pins 21 and 22)
  Wire.begin();  
  
  // Start the LCD screen
  lcd.begin();  
  lcd.print("Parking Lot");  // Initial message on the LCD
  delay(2000);
}

void loop() {
  // Read sensor states
  int sensorAState = digitalRead(SENSOR_A_PIN);
  int sensorBState = digitalRead(SENSOR_B_PIN);

  lcd.clear();  // Clear the screen before showing the next message

  if (sensorAState == HIGH && sensorBState == LOW) {
    // If sensor A is triggered first (car entering)
    if (totalCarsCounter < MAX_CARS) {  // Only allow entry if it's not full
      Serial.println("A car is entering.");
      lcd.print("A car is entering"); // Display message on the LCD
      myServo.write(180);            // Move servo to 180 degrees (open barrier)
      delay(2000);                   // Wait for 2 seconds
      myServo.write(90);             // Move servo to 90 degrees (close barrier)
      delay(1000);                   // Wait for 1 second to avoid multiple readings
      
      counterA++;  // Increment counter for incoming cars
      totalCarsCounter++;  // Increment total cars counter
      Serial.print("Counter A: ");
      Serial.println(counterA);
      Serial.print("Total Cars: ");
      Serial.println(totalCarsCounter);
      
      if (totalCarsCounter >= MAX_CARS) {
        lcd.clear();
        lcd.print("Parking Lot");
        lcd.setCursor(0, 1);
        lcd.print("FULL");
        Serial.println("Parking lot is full");
        delay(2000);
      }
    } else {
      Serial.println("No space to enter.");
      lcd.clear();
      lcd.print("No space");
      delay(2000);
    }
  } else if (sensorBState == HIGH && sensorAState == LOW) {
    // If sensor B is triggered first (car leaving)
    if (totalCarsCounter > 0) {  // Only allow exit if there are cars in the lot
      Serial.println("A car is leaving.");
      lcd.print("A car is leaving"); // Display message on the LCD
      myServo.write(180);            // Move servo to 180 degrees (open barrier)
      delay(2000);                   // Wait for 2 seconds
      myServo.write(90);             // Move servo to 90 degrees (close barrier)
      delay(1000);                   // Wait for 1 second to avoid multiple readings
      
      counterB++;  // Increment counter for outgoing cars
      totalCarsCounter--;  // Decrement total cars counter
      Serial.print("Counter B: ");
      Serial.println(counterB);
      Serial.print("Total Cars: ");
      Serial.println(totalCarsCounter);
      
      if (totalCarsCounter < MAX_CARS) {
        lcd.clear();
        lcd.print("Parking Lot");
        lcd.setCursor(0, 1);
        lcd.print("Space available");
        Serial.println("Space available");
        delay(2000);
      }
    } else {
      Serial.println("No cars to leave.");
      lcd.clear();
      lcd.print("No cars");
      delay(2000);
    }
  } else if (sensorAState == HIGH && sensorBState == HIGH) {
    // Both sensors activated at the same time (possible error or interference)
    Serial.println("Both sensors active.");
    lcd.print("ERROR: Both");    // Display error on the LCD
    delay(1000);
  }

  // Add a small delay to reduce processing load
  delay(100);
}
