#ifndef OUTPUT_H
#define OUTPUT_H

// Motor Control Pin Definitions
extern int mainMotorForwardPin;
extern int mainMotorBackwardPin;
extern int secondMotorForwardPin;
extern int secondMotorBackwardPin;
extern int capMotorForwardPin;
extern int capMotorBackwardPin;

// Function Prototypes
void setupMotors();
void forwardMotor(int pin1, int pin2);
void backwardMotor(int pin1, int pin2);
void stopMotor(int pin1, int pin2);

#endif // OUTPUT_H
