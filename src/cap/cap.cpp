#include "../../include/cap/cap.h"
#include "../../include/buttons/buttons.h"
#include "../../include/motors/motors.h"
#include "../../include/utils/flags.h"
#include "../../include/config/pins.h"

// Function to open the cap
bool openCap() {
    while (closeCapFlag) {
        if (oneFlag) {
            oneFlag = false;
            forwardMotor(CAP_MOTOR_FORWARD_PIN, CAP_MOTOR_BACKWARD_PIN);
        }
        if (checkPressed(openCapSwitch)) {
            stopMotor(CAP_MOTOR_FORWARD_PIN, CAP_MOTOR_BACKWARD_PIN);
            oneFlag = true;
            return true; // Return True
        }
    }
    return false;
}

// Function to close the cap
bool closeCap() {
    while (openCapFlag) {
        if (oneFlag) {
            oneFlag = false;
            backwardMotor(CAP_MOTOR_FORWARD_PIN, CAP_MOTOR_BACKWARD_PIN);
        }
        if (checkPressed(closeCapSwitch)) {
            stopMotor(CAP_MOTOR_FORWARD_PIN, CAP_MOTOR_BACKWARD_PIN);
            oneFlag = true;
            return true; // Return True
        }
    }
    return false;
} 