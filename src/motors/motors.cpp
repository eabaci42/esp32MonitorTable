#include "../../include/motors/motors.h"
#include "../../include/config/pins.h"
#include <Arduino.h>

// Initialize motor pins
void initMotors() {
    int motorPins[] = {
        MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN, 
        SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN, 
        CAP_MOTOR_FORWARD_PIN, CAP_MOTOR_BACKWARD_PIN
    };
    
    for (int pin : motorPins) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH); // Assume HIGH means motors are stopped
    }
}

// Function to move motor forward
void forwardMotor(int forwardPin, int backwardPin) {
    digitalWrite(forwardPin, LOW);   // Set forward pin LOW     - Enable
    digitalWrite(backwardPin, HIGH); // Set backward pin HIGH   - Disable
    Serial.println("forwardMotor");
}

// Function to move motor backward
void backwardMotor(int forwardPin, int backwardPin) {
    digitalWrite(forwardPin, HIGH); // Set forward pin HIGH    - Disable
    digitalWrite(backwardPin, LOW);  // Set backward pin LOW     - Enable
    Serial.println("backwardMotor");
}

// Function to stop motor
void stopMotor(int forwardPin, int backwardPin) {
    digitalWrite(forwardPin, HIGH);  // Set forward pin HIGH    - Disable
    digitalWrite(backwardPin, HIGH); // Set backward pin HIGH    - Disable
    Serial.println("stopMotor");
} 