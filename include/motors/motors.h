#ifndef MOTORS_H
#define MOTORS_H

// Initialize motor pins
void initMotors();

// Motor control functions
void forwardMotor(int forwardPin, int backwardPin);
void backwardMotor(int forwardPin, int backwardPin);
void stopMotor(int forwardPin, int backwardPin);

#endif // MOTORS_H 