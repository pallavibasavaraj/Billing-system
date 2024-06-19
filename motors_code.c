#include <NewPing.h>

// Sensor definitions
const int leftSensorPin = 2;
const int rightSensorPin = 3;
const int triggerPin = A0;
const int echoPin = A1;

// Motor control definitions (adjust based on your motor driver)
const int motorSpeedA1 = 9;
const int motorSpeedA2 = 10;
const int motorSpeedB1 = 11;
const int motorSpeedB2 = 12;

// Thresholds and settings
const int minDistance = 30; // cm
const int maxDistance = 50; // cm
const int beepPin = 8; // Pin for buzzer (optional)
const int beepDuration = 200; // ms

NewPing sonar(triggerPin, echoPin, maxDistance);

void setup() {
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
  pinMode(motorSpeedA1, OUTPUT);
  pinMode(motorSpeedA2, OUTPUT);
  pinMode(motorSpeedB1, OUTPUT);
  pinMode(motorSpeedB2, OUTPUT);
  pinMode(beepPin, OUTPUT); // Optional, set to OUTPUT only if using buzzer
  Serial.begin(9600);
}

void loop() {
  int distance = sonar.ping_cm();
  int leftSensor = digitalRead(leftSensorPin);
  int rightSensor = digitalRead(rightSensorPin);

  // Check if person is in range
  if (distance >= minDistance && distance <= maxDistance) {
    // Person in range, follow line
    followLine(leftSensor, rightSensor);

    // Check if person moved out of range (optional beep)
    if (distance < minDistance || distance > maxDistance) {
      Serial.println("Person moved out of range");
      beep(); // Optional beep
    }
  } else {
    // Person too close or too far, stop trolley
    Serial.println("Person too close or far, stopping");
    stopMotors();
  }

  delay(10); // Adjust delay as needed
}

void followLine(int leftSensor, int rightSensor) {
  // Implement your line following logic here based on sensor readings
  // Example:
  if (leftSensor == HIGH && rightSensor == HIGH) {
    // Both sensors on line, move forward
    forward();
  } else if (leftSensor == LOW && rightSensor == HIGH) {
    // Left sensor off line, turn right
    turnRight();
  } else if (leftSensor == HIGH && rightSensor == LOW) {
    // Right sensor off line, turn left
    turnLeft();
  } else {
    // Both sensors off line, stop or reverse (adjust as needed)
    stopMotors();
  }
}

void forward() {
  // Set motor speeds for forward motion
  // Example:
  analogWrite(motorSpeedA1, 255);
  analogWrite(motorSpeedA2, 0);
  analogWrite(motorSpeedB1, 255);
  analogWrite(motorSpeedB2, 0);
}

void turnRight() {
  // Set motor speeds for right turn
  // Example:
  analogWrite(motorSpeedA1, 0);
  analogWrite(motorSpeedA2, 255);
  analogWrite(motorSpeedB1, 255);
  analogWrite(motorSpeedB2, 0);
}

void turnLeft() {
  // Set motor speeds for left turn
  // Example:
  analogWrite(motorSpeedA1, 255);
  analogWrite(motorSpeedA2, 0);
  analogWrite(motorSpeedB1, 0);
  analogWrite(motorSpeedB2, 255);
}

void stopMotors() {
  // Set motor speeds to stop
  // Example:
  analogWrite(motorSpeedA1, 0);
  analogWrite(motorSpeedA2, 0);
  analogWrite(motorSpeedB1, 0);
  analogWrite(motorSpeedB2, 0);
}

void beep() {
  // Generate a beep sound on the buzzer pin
  // Example:
  digitalWrite(beepPin, HIGH);
  delay(beepDuration);
  digitalWrite(beepPin, LOW);
}
