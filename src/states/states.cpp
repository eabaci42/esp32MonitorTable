#include "../../include/states/states.h"
#include "../../include/states/fsm.h"
#include "../../include/buttons/buttons.h"
#include "../../include/motors/motors.h"
#include "../../include/cap/cap.h"
#include "../../include/utils/flags.h"
#include "../../include/config/pins.h"
#include <Arduino.h>

void startState() {
    Serial.println("Start state");
    // Check button state and make transitions
    if (checkPressed(upButton)) {
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(OPENCAP); // Transition to Open Cap state when UpButton is pressed
    } else {
        if (oneFlag) {
            oneFlag = false;
            fsm.transitionTo(START);
        }
    }
}

void openCapState() {
    if (startFlag) {
        // Check if the function is being called with proper authorization
        Serial.println("Open Cap State");
        if (!openCapFlag) {
            // Check if the cap is not already open
            if (openCap()) { // Perform cap opening operation
                openCapFlag = true;
                closeCapFlag = false;
                fsm.transitionTo(Y_RISING); // Transition to Y-axis rising state after cap opening
            } else {
                // Transition to error state if cap opening operation fails
                fsm.transitionTo(ERROR);
                updateErrorMessage("E02X003"); // E02X003 -> Error occurred during cap opening operation
            }
        } else {
            // Transition to error state if openCapFlag is in an unexpected state
            fsm.transitionTo(ERROR);
            updateErrorMessage("E02X002"); // E02X002 -> openCapFlag has an unexpected value
        }
    } else {
        // Transition to error state if the function is called without proper authorization
        fsm.transitionTo(ERROR);
        updateErrorMessage("E02X001"); // E02X001 -> Unauthorized access to openCapState function
    }
}

void closeCapState() {
    if (finalFlag) {
        // Check if the function is being called with proper authorization
        Serial.println("Close Cap State");
        if (!closeCapFlag) {
            // Check if the cap is not already closed
            if (closeCap()) { // Perform cap closing operation
                closeCapFlag = true;
                openCapFlag = false;
                fsm.transitionTo(START); // Transition to START state after cap closing
            } else {
                // Transition to error state if cap closing operation fails
                fsm.transitionTo(ERROR);
                updateErrorMessage("E03X003"); // E03X003 -> Error occurred during cap closing operation
            }
        } else {
            // Transition to error state if closeCapFlag is in an unexpected state
            fsm.transitionTo(ERROR);
            updateErrorMessage("E03X002"); // E03X002 -> closeCapFlag has an unexpected value
        }
    } else {
        // Transition to error state if the function is called without proper authorization
        fsm.transitionTo(ERROR);
        updateErrorMessage("E03X001"); // E03X001 -> Unauthorized access to closeCapState function
    }
}

void yrisingState() {
    Serial.println("Y Rising State");
    if (checkPressed(ymaxSwitch)) {
        stopMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
        oneFlag = true;
        fsm.transitionTo(YZ_VERTICAL);
    } else if (checkPressed(stopButton)) {
        stopMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
        startFlag = false;
        finalFlag = false;
        stopFlag = true;
        oneFlag = true;
        fsm.transitionTo(Y_MIDDLE);
    } else if (checkPressed(downButton)) {
        stopMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_FALLING);
    } else {
        if (oneFlag) {
            oneFlag = false;
            forwardMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
        }
    }
}

void ymiddleState() {
    Serial.println("Y Middle State");
    if (checkPressed(upButton)) {
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_RISING);
    } else if (checkPressed(downButton)) {
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_FALLING);
    } else {
        if (oneFlag) {
            oneFlag = false;
            fsm.transitionTo(Y_MIDDLE);
        }
    }
}

void yfallingState() {
    Serial.println("Y Falling State");
    if (checkPressed(startSwitch)) {
        stopMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
        oneFlag = true;
        fsm.transitionTo(CLOSECAP);
    } else if (checkPressed(upButton)) {
        stopMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_RISING);
    } else if (checkPressed(stopButton)) {
        stopMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
        startFlag = false;
        finalFlag = false;
        stopFlag = true;
        oneFlag = true;
        fsm.transitionTo(Y_MIDDLE);
    } else {
        if (oneFlag) {
            oneFlag = false;
            backwardMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
        }
    }
}

void yzverticalState() {
    Serial.println("YZ Vertical State");
    if (startFlag) {
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    } else if (finalFlag) {
        oneFlag = true;
        fsm.transitionTo(Y_FALLING);
    } else {
        if (oneFlag) {
            oneFlag = false;
            stopMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
            stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        }
    }
}

void zverticalState() {
    Serial.println("Z Vertical State");
    if (checkPressed(upButton)) {
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    } else if (checkPressed(downButton)) {
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Y_FALLING);
    } else if (checkPressed(horizontalButton)) {
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    } else {
        if (oneFlag) {
            oneFlag = false;
            stopMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
            stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        }
    }
}

void zrisingState() {
    Serial.println("Z Rising State");
    if (checkPressed(finalSwitch)) {
        stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        oneFlag = true;
        fsm.transitionTo(PRESENTATION);
    } else if (checkPressed(stopButton)) {
        stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        startFlag = false;
        finalFlag = false;
        stopFlag = true;
        oneFlag = true;
        fsm.transitionTo(Z_MIDDLE);
    } else if (checkPressed(downButton)) {
        stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    } else if (checkPressed(verticalButton)) {
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    } else {
        if (oneFlag) {
            oneFlag = false;
            forwardMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        }
    }
}

void zmiddleState() {
    Serial.println("Z Middle State");
    if (checkPressed(upButton)) {
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    } else if (checkPressed(downButton)) {
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    } else if (checkPressed(verticalButton)) {
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    } else if (checkPressed(horizontalButton)) {
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    } else {
        if (oneFlag) {
            oneFlag = false;
            fsm.transitionTo(Z_MIDDLE);
        }
    }
}

void zfallingState() {
    Serial.println("Z Falling State");
    if (checkPressed(verticalSwitch)) {
        stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        oneFlag = true;
        if (finalFlag)
            fsm.transitionTo(YZ_VERTICAL);
        else
            fsm.transitionTo(Z_VERTICAL);
    } else if (checkPressed(upButton)) {
        stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        startFlag = true;
        finalFlag = false;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    } else if (checkPressed(stopButton)) {
        stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        startFlag = false;
        finalFlag = false;
        stopFlag = true;
        oneFlag = true;
        fsm.transitionTo(Z_MIDDLE);
    } else if (checkPressed(horizontalButton)) {
        oneFlag = true;
        fsm.transitionTo(Z_RISING);
    } else {
        if (oneFlag) {
            oneFlag = false;
            backwardMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        }
    }
}

void presentationState() {
    Serial.println("Presentation State");
    if (checkPressed(downButton)) {
        stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        startFlag = false;
        finalFlag = true;
        stopFlag = false;
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    } else if (checkPressed(verticalButton)) {
        oneFlag = true;
        fsm.transitionTo(Z_FALLING);
    } else {
        if (oneFlag) {
            oneFlag = false;
            stopMotor(MAIN_MOTOR_FORWARD_PIN, MAIN_MOTOR_BACKWARD_PIN);
            stopMotor(SECOND_MOTOR_FORWARD_PIN, SECOND_MOTOR_BACKWARD_PIN);
        }
    }
}

void undefinedState() {
    // Empty implementation
}

void errorState() {
    // Empty implementation
} 