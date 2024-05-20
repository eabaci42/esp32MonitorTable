#include "output.h"
#include <Arduino.h>

// Motor Control Pin Definitions
int mainMotorForwardPin = 23;
int mainMotorBackwardPin = 22;
int secondMotorForwardPin = 3;
int secondMotorBackwardPin = 21;
int capMotorForwardPin = 19;
int capMotorBackwardPin = 18;

void setupMotors() {
    int motorPins[] = {mainMotorForwardPin, mainMotorBackwardPin, secondMotorForwardPin, secondMotorBackwardPin, capMotorForwardPin, capMotorBackwardPin};
    for (int pin : motorPins) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH); // Assume HIGH means motors are stopped
    }
}

void forwardMotor(int pin1, int pin2) {
    digitalWrite(pin1, LOW);  // Set pin1 LOW     - Enable
    digitalWrite(pin2, HIGH); // Set pin2 HIGH    - Disable
    Serial.println("forwardMotor");
}

void backwardMotor(int pin1, int pin2) {
    digitalWrite(pin1, HIGH); // Set pin1 HIGH    - Disable
    digitalWrite(pin2, LOW);  // Set pin2 LOW     - Enable
    Serial.println("backwardMotor");
}

void stopMotor(int pin1, int pin2) {
    digitalWrite(pin1, HIGH); // Set pin1 HIGH    - Disable
    digitalWrite(pin2, HIGH); // Set pin2 HIGH    - Disable
    Serial.println("stopMotor");
}
